#version 410 core
in vec3 vnormal;
in vec3 vposition;
in vec3 vcolor;
in vec2 vtexCoord;

out vec4 color;

void main(void)
{
    color = vec4(vnormal, 0.0);
}
