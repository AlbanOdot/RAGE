#include "MyShaderProgram.h"
#include <gl3.h>
#include <iostream>

MyShaderProgram::MyShaderProgram(){}
MyShaderProgram::~MyShaderProgram(){}

MyShaderProgram::MyShaderProgram(GLuint VS, GLuint TC, GLuint TE, GLuint Geo, GLuint Frag) :
vertexShader(VS),tesselationControlShader(TC),tesselationEvaluationShader(TE), geometryShader(Geo), fragmentShader(Frag)
{
    int success = 0;
    GLchar infoLog[512];
    program = glCreateProgram();
    glAttachShader(program,vertexShader);
    glAttachShader(program,tesselationControlShader);
    glAttachShader(program,tesselationEvaluationShader);
    glAttachShader(program,geometryShader);
    glAttachShader(program, fragmentShader);
    glBindAttribLocation(program,0,"Position");
    glLinkProgram(program);
    glGetProgramiv(program, GL_LINK_STATUS, &success);
    if(!success){
        glGetProgramInfoLog(program, 512,NULL,infoLog);
        std::cerr << "ERROR::SHADER::LINK_FAILED\n"<<infoLog<<std::endl;
    }
}

MyShaderProgram::MyShaderProgram(GLuint VS, GLuint Frag){

}

void MyShaderProgram::addVertex(GLuint VS){

}
void MyShaderProgram::addTesselation( GLuint TC, GLuint TE){

}
void MyShaderProgram::addGeometry( GLuint Geo){

}
void MyShaderProgram::addFragment(GLuint Frag){

}
