#version 410 core


uniform vec4 models[20]; //#define MAX_BONES_COUNT 5 -> AnimatedModel.h + m_model de Model.h
uniform mat4 view;
uniform mat4 projection;
uniform bool animated;

layout (location = 0) in vec3 iposition;
layout (location = 1) in vec3 inormal;
layout (location = 2) in vec3 icolor;
layout (location = 3) in vec2 itexCoord;
layout (location = 4) in vec4 weights;
layout (location = 5) in vec4 weightsIdx;



out vec3 vnormal;
out vec3 vposition;
out vec4 vcolor;
out vec2 vtexCoord;

void main()
{
    mat4 model = models[0];
    gl_Position = projection * view * model * vec4(iposition, 1.0f);
    //On fait ca pour que la position soit interpolée
    vposition = vec3(view * model * vec4(iposition, 1.0f));
    //Passthrough
    vnormal = normalize(vec3(model * vec4(inormal, 1.0f)));
    vcolor = vec4(0.4,0.4,0.4,1.0f);
    vtexCoord = itexCoord;
}
