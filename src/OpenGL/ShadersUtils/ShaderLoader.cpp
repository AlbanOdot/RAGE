#include "ShaderLoader.h"
#include <iostream>
#include <fstream>
#include <cstdio>

ShaderLoader::ShaderLoader(){}
ShaderLoader::~ShaderLoader(){}

ShaderLoader::ShaderLoader(const char * shaderPath, int  t, const char * error){
    std::ifstream infile { shaderPath };
    std::string file_contents { std::istreambuf_iterator<char>(infile), std::istreambuf_iterator<char>() };
    const char * shaderSource = file_contents.c_str();
    type = t;
    // Initialize shaders
    GLint success;
    GLchar infoLog[1000]; // warning fixed size ... request for LOG_LENGTH!!!
    /* I. Creation et compilation du shader */
    shader = glCreateShader(t);
    glShaderSource(shader, 1, &shaderSource, NULL);
    glCompileShader(shader);
    glGetShaderiv(shader, GL_COMPILE_STATUS, &success);
    if(!success) {
        glGetShaderInfoLog(shader, 512, NULL, infoLog);
        std::cerr << "ERROR::SHADER::"<<error<<"::COMPILATIONFAILED\n"<<infoLog<<std::endl;
    }
}
