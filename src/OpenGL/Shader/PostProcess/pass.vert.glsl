#version 410 core
        layout (location = 0) in vec2 iposition;
        layout (location = 1) in vec2 itexCoord;

        out vec2 vtexCoord;
        out vec2 vposition;
void main()
{

        // Note that we read the multiplication from right to left
        gl_Position = vec4(iposition.x, iposition.y, 0.0, 1.0);
        vposition = iposition;
        vtexCoord = itexCoord;
}
