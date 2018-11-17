#version 410 core
        layout (location = 0) in vec3 iposition;
        layout (location = 1) in vec3 inormal;
        layout (location = 2) in vec3 icolor;
        layout (location = 3) in vec2 itexCoord;
        uniform mat4 model;
        uniform mat4 view;
        uniform mat4 projection;
        out vec3 vnormal;
        out vec3 vposition;
        out vec3 vcolor;
        out vec2 vtexCoord;
void main()
{
            // Note that we read the multiplication from right to left
            gl_Position = projection * view * model * vec4(iposition, 1.0f);

            //On fait ca pour que la position soit interpolée
            //vec4 p = model*vec4(iposition, 1.0f);
            vposition = vec3(view * model * vec4(iposition, 1.0f));//(p / p.w).xyz;

            //Passthrough
            vnormal = inormal;
            vcolor = icolor;
            vtexCoord = itexCoord;
}
