#version 410 core
out float color;

in vec2 vtexCoord;

uniform sampler2D ssaoTexture;

void main()
{
    vec2 texelSize = 1.0 / vec2(textureSize(ssaoTexture, 0));
    float result = 0.0;
    for (int x = -2; x < 2; ++x)
    {
        for (int y = -2; y < 2; ++y)
        {
            vec2 offset = vec2(float(x), float(y)) * texelSize;
            result += texture(ssaoTexture, vtexCoord + offset).r;
        }
    }
    color = result / 16.;
}
