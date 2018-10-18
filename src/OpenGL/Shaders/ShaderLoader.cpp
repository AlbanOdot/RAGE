#include "ShaderLoader.h"
#include <iostream>

ShaderLoader::ShaderLoader(){}
ShaderLoader::~ShaderLoader(){}

ShaderLoader::ShaderLoader(const char * shaderSource, GLenum  t, const std::string& error){
    type = t;
    // Initialize shaders
    GLint success;
    GLchar infoLog[512]; // warning fixed size ... request for LOG_LENGTH!!!
    /* I. Creation et compilation du shader */
    shader = glCreateShader(t);
    glShaderSource(shader, 1, &shaderSource, NULL);
    glCompileShader(shader);
    glGetShaderiv(shader, GL_COMPILE_STATUS, &success);
    if(!success) {
        glGetShaderInfoLog(shader, 512, NULL, infoLog);
        std::cerr << "ERROR::SHADER::"<<error<<":: COMPILATIONFAILED\n"<<infoLog<<std::endl;
    }
}
