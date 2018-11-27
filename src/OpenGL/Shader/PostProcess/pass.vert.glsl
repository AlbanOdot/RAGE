#version 410 core
in vec2 iposition;
in vec2 itexCoord;

out vec2 vtexCoord;
void main()
{

        // Note that we read the multiplication from right to left
        gl_Position = vec4(iposition.x, iposition.y, 0.0, 1.0);
        vtexCoord = itexCoord;
}
