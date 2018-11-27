#version 410 core
out float color;

in vec2 vtexCoord;

uniform sampler2D position;
uniform sampler2D normal;
uniform sampler2D noise;

uniform vec3 kernel[64];

int kernelSize = 64;
uniform float radius;
uniform float bias;

uniform vec2 noiseScale;

uniform mat4 projection;

void main()
{
    vec3 fragPos = texture(position, vtexCoord).xyz;
    vec3 normal = normalize(texture(normal, vtexCoord).rgb);
    vec3 randomVec = normalize(texture(noise, vtexCoord * noiseScale).xyz);

    vec3 tangent = normalize(randomVec - normal * dot(randomVec, normal));
    vec3 bitangent = cross(normal, tangent);
    mat3 TBN = mat3(tangent, bitangent, normal);

    float occlusion = 0.0;

    for(int i = 0; i<kernelSize; ++i)
    {
        vec3 samp = TBN * kernel[i];
        samp = fragPos + samp * radius;
        vec4 offset = vec4(samp, 1.0);
        offset = projection * offset;
        offset.xyz /= offset.w;
        offset.xyz = offset.xyz * 0.5 +0.5;

        float sampleDepth = texture(position, offset.xy).z;

        float rangeCheck = smoothstep(0.0, 1.0, radius / abs(fragPos.z - sampleDepth));
        occlusion += (sampleDepth >= samp.z + bias ? 1.0 : 0.0) * rangeCheck;
    }
    color = 1.0 - (occlusion / kernelSize);
}
