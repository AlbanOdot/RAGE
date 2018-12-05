#version 410 core
layout (location = 0) in vec3 iposition;
layout (location = 1) in vec3 inormal;
layout (location = 2) in vec3 icolor;
layout (location = 3) in vec2 itexCoord;

uniform mat4 models[5]; //#define MAX_BONES_COUNT 25 -> AnimatedModel.h + m_model de Model.h

uniform mat4 view;
uniform mat4 projection;

out vec3 vnormal;
out vec3 vposition;
out vec3 vcolor;
out vec2 vtexCoord;

void main()
{
    //On lit à la bonne colonne grâce à gl_VertexID
    mat4 model = models[0];
    /*if(animated){
        vec2 weightSize = vec2(textureSize(weights, 0));
        for(int i = 0; i < weightSize.r; ++i){
            // La texture de poids prends un os en ligne et un vertex en colonne
            model *= models[i + 1] * texelFetch(weights,ivec2(i,gl_VertexID), 0).r;
        }
    }*/

    gl_Position = projection * view * model * vec4(iposition, 1.0f);
    //On fait ca pour que la position soit interpolée
    vposition = vec3(view * model * vec4(iposition, 1.0f));

    //Passthrough
    vnormal = inormal;
    vcolor = inormal;
    vtexCoord = itexCoord;
}
