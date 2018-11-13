#version 410 core
in vec3 vnormal;
in vec3 vposition;
in vec3 vcolor;
in vec2 vtexCoord;

layout(location = 0) out vec3 position;
layout(location = 1) out vec3 normal;
layout(location = 2) out vec3 color;
void main()
{
    position = vposition;
    normal = vnormal;
    color = vec4(vec3(0.95), 1.0f);//A changer en couleur de la texture si les coordonnées sont pas invalides;
}
