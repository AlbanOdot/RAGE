#version 410 core
out vec4 color;

in vec2 vtexCoord;

uniform sampler2D screenTexture;
uniform sampler2D brightTexture;
uniform float gamma;
uniform float exposure;
uniform bool computeHDR;
uniform float BLOOM;

void main()
{
    vec3 hdrColor = texture(screenTexture, vtexCoord).rgb;
    if(!computeHDR){
        color = vec4(hdrColor,1.0);
        return;
    }

    vec3 bri = texture(brightTexture, vtexCoord).rgb;
    hdrColor += BLOOM * bri;
    vec3 mapped =vec3(1.0) - exp(-hdrColor * exposure);

    mapped = pow(mapped,vec3(1.0/gamma));
    color = vec4(mapped, 1.0);
}
