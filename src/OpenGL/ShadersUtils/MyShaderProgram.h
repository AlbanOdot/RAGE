#ifndef _MyShaderProgram
#define _MyShaderProgram

#include "./src/OpenGL/opengl_stuff.h"

class MyShaderProgram{
public:
    MyShaderProgram();
    ~MyShaderProgram();
    MyShaderProgram(GLuint& VS, GLuint& TC, GLuint& TE, GLuint& Geo, GLuint& Frag);
    MyShaderProgram(GLuint& VS, GLuint& Frag);

    void addVertex(GLuint VS);
    void addTesselation( GLuint TC, GLuint TE);
    void addGeometry( GLuint Geo);
    void addFragment(GLuint Frag);

    GLuint getProgram() { return program;}
    //GLuint getUniformLocation(const char * name) { return glGetUniformLocation(program,name);}

private:

    GLuint program;
    GLuint vertexShader;
    GLuint tesselationControlShader;
    GLuint tesselationEvaluationShader;
    GLuint geometryShader;
    GLuint fragmentShader;

};

#endif
