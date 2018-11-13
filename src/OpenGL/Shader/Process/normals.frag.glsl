#version 410 core
        in vec3 vnormal;
        in vec3 vposition;
        in vec3 vcolor;
        in vec2 vtexCoord;
        layout(location = 0) out vec4 color;
void main()
{
            color = vec4(vnormal*0.5+0.5, 1.0f);
}
