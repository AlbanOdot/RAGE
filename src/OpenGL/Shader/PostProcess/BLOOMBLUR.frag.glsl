#version 410 core
out vec4 color;

in vec2 vtexCoord;

uniform sampler2D screenTexture;

uniform float horizontal;
uniform float weights1[6] = float[6] (0.119726,0.116061,0.105726,0.090506,0.072806,0.055037);
uniform float weights2[8] = float[8](0.011218,0.010875,0.009906,0.00848,0.006822,0.005157,0.003663,0.002445);
uniform float weights3[12] = float[12](0.09988,0.096823,0.088201,0.075504,0.060738,0.045914,0.032616,0.021773,0.013658,0.008051,0.00446,0.002322);
uniform float weights4[3] = float[3](0.212543,0.206038,0.187691);
uniform vec2 texelStep;

void main()
{
    vec3 finalCol = vec3(0.0);
    vec3 Color[23];
    for(int i = 0; i < 11; ++i){
        Color[11+i] = texture(screenTexture, vtexCoord + vec2((1.0-horizontal) * texelStep.x * i, texelStep.y * i * horizontal)).rgb;
        Color[i] = texture(screenTexture, vtexCoord - vec2((1.0 - horizontal) * texelStep.x * i, texelStep.y * i * horizontal)).rgb;
    }

    //Kernel size = 11
    vec3 col = Color[11] * weights1[0];
    for(int i=1; i < 6; ++i)
    {
        col += Color[i] * weights1[i];
        col += Color[i] * weights1[i];
    }
    finalCol += col;
    //Kernel size = 15
    col = Color[11] * weights2[0];
    for(int i=1; i < 8; ++i)
    {
        col += Color[i] * weights2[i];
        col += Color[i] * weights2[i];
    }
    finalCol += col;

    //Kernel size = 23
    col = Color[11] * weights3[0];
    for(int i=1; i < 11; ++i)
    {
        col += Color[i] * weights3[i];
        col += Color[i] * weights3[i];
    }
    finalCol += col;

    //Kernel size = 5
    col = Color[11] * weights4[0];
    for(int i=1; i < 3; ++i)
    {
        col += Color[i] * weights4[i];
        col += Color[i] * weights4[i];
    }
    finalCol += col;

    finalCol /= 4;
    color = vec4(finalCol, 1.0);
}
