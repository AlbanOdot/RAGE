#version 410 core
in vec3 vnormal;
in vec3 vposition;
in vec4 vcolor;
in vec2 vtexCoord;

layout(location = 0) out vec3 position;
layout(location = 1) out vec3 normal;
layout(location = 2) out vec4 albedo;

void main()
{
    position = vposition;
    normal = vnormal;
    albedo = vcolor;
}
