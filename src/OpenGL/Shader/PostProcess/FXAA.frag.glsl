#version 410 core

#define EDGE_THRESHOLD_MIN 0.0312
#define EDGE_THRESHOLD_MAX 0.125
#define ITERATIONS 10
#define SUBPIXEL_QUALITY 0.75

float rgb2luma(vec4 rgba){
    return sqrt(dot(rgba, vec4(0.299, 0.587, 0.114, 0.0)));
}

float cfloat(bool c){
    return c ? 1.0 : 0.0;
}


in vec2 vposition;
in vec2 vtexCoord;

uniform sampler2D position;
uniform sampler2D normal;
uniform sampler2D albedo;
uniform sampler2D screenTexture;

uniform vec2 inverseScreenSize;
uniform bool showContour;
uniform bool computeFXAA;
uniform float minThreshold;
uniform float maxThreshhold;

out vec4 color;

void main()
{

    vec4 colorCenter = texture(screenTexture,vtexCoord);
    if(!computeFXAA){
        color = colorCenter;
        return;
    }

    //Approxiamtion
    float lumaCenter = rgb2luma(colorCenter);
    float lumaDown = rgb2luma(textureOffset(screenTexture,vtexCoord,ivec2(0,-1)));
    float lumaUp = rgb2luma(textureOffset(screenTexture,vtexCoord,ivec2(0,1)));
    float lumaLeft = rgb2luma(textureOffset(screenTexture,vtexCoord,ivec2(-1,0)));
    float lumaRight = rgb2luma(textureOffset(screenTexture,vtexCoord,ivec2(1,0)));
    float lumaMin = min(lumaCenter,min(min(lumaDown,lumaUp),min(lumaLeft,lumaRight)));
    float lumaMax = max(lumaCenter,max(max(lumaDown,lumaUp),max(lumaLeft,lumaRight)));
    float lumaRange = lumaMax - lumaMin;

    //Si la modification est sera asser visible on continue
    if(lumaRange < max(minThreshold,lumaMax*maxThreshhold)){
        float s = cfloat(showContour);
        color = s * vec4(vec3(lumaCenter * 0.25),1.0) + (1.0 - s) * colorCenter;
        return;
    }

    //Gradient dans toutes les directions
    float lumaDownLeft = rgb2luma(textureOffset(screenTexture,vtexCoord,ivec2(-1,-1)));
    float lumaUpRight = rgb2luma(textureOffset(screenTexture,vtexCoord,ivec2(1,1)));
    float lumaUpLeft = rgb2luma(textureOffset(screenTexture,vtexCoord,ivec2(-1,1)));
    float lumaDownRight = rgb2luma(textureOffset(screenTexture,vtexCoord,ivec2(1,-1)));

    float lumaDownUp = lumaDown + lumaUp;
    float lumaLeftRight = lumaLeft + lumaRight;
    float lumaLeftCorners = lumaDownLeft + lumaUpLeft;
    float lumaDownCorners = lumaDownLeft + lumaDownRight;
    float lumaRightCorners = lumaDownRight + lumaUpRight;
    float lumaUpCorners = lumaUpRight + lumaUpLeft;

    float edgeHorizontal =  abs(-2.0 * lumaLeft + lumaLeftCorners)  + abs(-2.0 * lumaCenter + lumaDownUp ) * 2.0    + abs(-2.0 * lumaRight + lumaRightCorners);
    float edgeVertical =    abs(-2.0 * lumaUp + lumaUpCorners)      + abs(-2.0 * lumaCenter + lumaLeftRight) * 2.0  + abs(-2.0 * lumaDown + lumaDownCorners);

    float isHorizontal = cfloat(edgeHorizontal >= edgeVertical);

    //Orientation de la pente
    float luma1 = isHorizontal == 1.0 ? lumaDown : lumaLeft;
    float luma2 = isHorizontal == 1.0 ? lumaUp : lumaRight;

    float gradient1 = luma1 - lumaCenter;
    float gradient2 = luma2 - lumaCenter;

    float is1Steepest = cfloat(abs(gradient1) >= abs(gradient2));
    float gradientScaled = 0.25*max(abs(gradient1),abs(gradient2));

    float stepLength = isHorizontal == 1.0 ? inverseScreenSize.y : inverseScreenSize.x;
    float lumaLocalAverage = 0.0;
    stepLength -= (2.0 * is1Steepest) * stepLength;
    lumaLocalAverage = 0.5*(luma1 + lumaCenter);
    vec2 currentUv = vtexCoord;
    currentUv.y += isHorizontal * stepLength * 0.5;
    currentUv.x += (1.0 - isHorizontal) * stepLength * 0.5;


    //Exploration de l'espace
    vec2 offset = isHorizontal == 1.0 ? vec2(inverseScreenSize.x,0.0) : vec2(0.0,inverseScreenSize.y);
    vec2 uv1 = currentUv ;
    vec2 uv2 = currentUv ;
    float lumaEnd1 = 0.0, lumaEnd2 = 0.0;
    float reached1 = 0.0, reached2 = 0.0, reachedBoth = 0.0;
    float quality[10] = float[10](1.0f,1.0f,1.0f,1.5f,2.0f,2.0f,2.0f,2.0f,4.0f,8.0f);
    for(int i = 0; reachedBoth == 0.0 && i < ITERATIONS; i++){
        lumaEnd1 = (1.0 - reached1) * (rgb2luma(texture(screenTexture, uv1)) - lumaLocalAverage);
        lumaEnd2 = (1.0 - reached1) * (rgb2luma(texture(screenTexture, uv2)) - lumaLocalAverage);
        reached1 = cfloat(abs(lumaEnd1) >= gradientScaled);
        reached2 = cfloat(abs(lumaEnd2) >= gradientScaled);
        reachedBoth = cfloat(reached1 == 1.0 && reached2 == 1.0);
        uv1 -= offset * (1.0 - reached1) * quality[i];
        uv2 += offset * (1.0 - reached2) * quality[i];
    }

    //Estimation de l'offset
    float distance1 = isHorizontal == 1.0 ? (vtexCoord.x - uv1.x) : (vtexCoord.y - uv1.y);
    float distance2 = isHorizontal == 1.0 ? (uv2.x - vtexCoord.x) : (uv2.y - vtexCoord.y);
    bool isDirection1 = distance1 < distance2;

    float distanceFinal = isDirection1 ? distance1 : distance2;
    float edgeThickness = (distance1 + distance2);
    float pixelOffset = - distanceFinal / edgeThickness + 0.5;
    bool isLumaCenterSmaller = lumaCenter < lumaLocalAverage;

    bool correctVariation = ((isDirection1 ? lumaEnd1 : lumaEnd2) < 0.0) != isLumaCenterSmaller;
    float finalOffset = correctVariation ? pixelOffset : 0.0;

    //Antialiasing
    float lumaAverage = (1.0/12.0) * (2.0 * (lumaDownUp + lumaLeftRight) + lumaLeftCorners + lumaRightCorners);
    float subPixelOffset1 = clamp(abs(lumaAverage - lumaCenter)/lumaRange,0.0,1.0);
    float subPixelOffset2 = (-2.0 * subPixelOffset1 + 3.0) * subPixelOffset1 * subPixelOffset1;
    float subPixelOffsetFinal = subPixelOffset2 * subPixelOffset2 * SUBPIXEL_QUALITY;
    finalOffset = max(finalOffset,subPixelOffsetFinal);

    //Couleur finale
    vec2 finalUv = vtexCoord;
    finalUv.y += finalOffset * isHorizontal * stepLength;
    finalUv.x += finalOffset * (1.0 - isHorizontal) * stepLength;
    color = texture(screenTexture,finalUv);

}
