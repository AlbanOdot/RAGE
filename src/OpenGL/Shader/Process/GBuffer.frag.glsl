#version 410 core
in vec3 vnormal;
in vec3 vposition;
in vec3 vcolor;
in vec2 vtexCoord;

layout(location = 0) out vec3 position;
layout(location = 1) out vec3 normal;
layout(location = 2) out vec4 albedo;

void main()
{
    position = vposition;
    normal = vnormal;
    albedo = vec4(normal * 0.5 + 0.5,1.0);//vec4(0.0,0.38,0.0, 1.0f);
}
