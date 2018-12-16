#version 410 core


uniform mat4 models[20]; //#define MAX_BONES_COUNT 5 -> AnimatedModel.h + m_model de Model.h
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
out vec3 vcolor;
out vec2 vtexCoord;

void main()
{
    //On lit à la bonne colonne grâce à gl_VertexID
    mat4 model = models[0];
    /*if(animated){
        model =  weights.x * models[int(weightsIdx.x)];
                + models[int(weightsIdx.y)] * weights.y
                + models[int(weightsIdx.z)] * weights.z
                + models[int(weightsIdx.w)] * weights.w;
    }*/

    gl_Position = projection * view * model * vec4(iposition, 1.0f);
    //On fait ca pour que la position soit interpolée
    vposition = vec3(view * model * vec4(iposition, 1.0f));

    //Passthrough
    vnormal = inormal;
    if( animated ){
        vcolor = vec3(0.20);//vec3(weights.z,weights.w,weights.x);
    }else
        vcolor = vec3(0.20);

    vtexCoord = itexCoord;
}
