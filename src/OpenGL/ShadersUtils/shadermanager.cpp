#include "shadermanager.h"
#include "ShaderLoader.h"
#include <iostream>

ShaderManager::ShaderManager()
{
    active_postprogram = -1;
    active_program = -1;
}


/*
 *
 * BASIC OBJECT DRAW FUNCTION
 *
 */
//Program add and remove
void ShaderManager::addProgram(const GLuint& newProg){
    program_m.push_back(newProg);
}

//Compute and add the corresponding program
GLuint ShaderManager::computeAddProgramm( const std::string& vs, const std::string& fs){
    ShaderLoader _loader;
    _loader = ShaderLoader(vs.c_str(),GL_VERTEX_SHADER,"VERTEX");
    GLuint vsid = _loader.getShader();
    _loader = ShaderLoader(fs.c_str(),GL_FRAGMENT_SHADER,"FRAGMENT");
    GLuint fsid = _loader.getShader();

    int success = 0;
    GLchar infoLog[512];
    GLuint program;
    program = glCreateProgram();
    glAttachShader(program,vsid);
    glAttachShader(program, fsid);
    glLinkProgram(program);
    glGetProgramiv(program, GL_LINK_STATUS, &success);
    if(!success){
        glGetProgramInfoLog(program, 512,NULL,infoLog);
        std::cerr << "ERROR::SHADER::LINK_FAILED\n"<<infoLog<<std::endl;
    }
    addProgram(program);
    return program;
}

//Remove the program of ID prog
void ShaderManager::removeProgram( const GLuint& prog){
    if(program_m[active_program] == prog)
        active_program = -1;
    for( auto p = program_m.begin(); p != program_m.end(); ++p){
        if(prog == *p)
            program_m.erase(p);
    }

}
//Remove the i'th programme
void ShaderManager::removeProgram( const int& i){
    if( i >= 0 && i < program_m.size()){
        GLuint prog = program_m[i];
        removeProgram(prog);
    }
}


//GETTER and SETTER
GLuint ShaderManager::getActiveProg(void) const{
    return program_m[active_program];
}
GLuint ShaderManager::setActiveProg(const GLuint& prog){
    unsigned int i = 0;
    for(    ; i < program_m.size(); ++i){
        if(prog == program_m[i])
            break;
    }
    active_program = i;
    return program_m[active_program];
}
GLuint ShaderManager::setActiveProg(const int& i){

    if( i >= 0 && i < program_m.size()){
        active_program = i;
    }
    return program_m[active_program];
}

unsigned int ShaderManager::progCount(){
    return program_m.size();
}

/*
 *
 * POST-PROCESS DRAW FUNCTION
 *
 */
//Program add and remove
void ShaderManager::addPostProgram(const GLuint& newProg){
    postProgram_m.push_back(newProg);
}

//Compute and add the corresponding postprocess programme
GLuint ShaderManager::computeAddPostProgramm( const std::string& vs, const std::string& fs){
    ShaderLoader _loader;
    _loader = ShaderLoader(vs.c_str(),GL_VERTEX_SHADER,"VERTEX");
    GLuint vsid = _loader.getShader();
    _loader = ShaderLoader(fs.c_str(),GL_FRAGMENT_SHADER,"FRAGMENT");
    GLuint fsid = _loader.getShader();

    int success = 0;
    GLchar infoLog[512];
    GLuint program;
    program = glCreateProgram();
    glAttachShader(program,vsid);
    glAttachShader(program, fsid);
    glLinkProgram(program);
    glGetProgramiv(program, GL_LINK_STATUS, &success);
    if(!success){
        glGetProgramInfoLog(program, 512,NULL,infoLog);
        std::cerr << "ERROR::SHADER::LINK_FAILED\n"<<infoLog<<std::endl;
    }
    addPostProgram(program);
    return program;
}

//Remove the program of ID prog
void ShaderManager::removePostProgram( const GLuint& prog){
    if(postProgram_m[active_postprogram] == prog)
        active_postprogram = -1;
    for( auto p = postProgram_m.begin(); p != postProgram_m.end(); ++p){
        if(prog == *p)
            postProgram_m.erase(p);
    }
}

//Remove the i'th programme
void ShaderManager::removePostProgram( const int& i){
    if( i >= 0 && i < postProgram_m.size()){
        GLuint prog = postProgram_m[i];
        removePostProgram(prog);
    }
}
//GETTER and SETTER
GLuint ShaderManager::getActivePostProg(void) const{
    return postProgram_m[active_postprogram];
}
GLuint ShaderManager::setActivePostProg(const GLuint& prog){
    int i = 0;
    for(    ; i < postProgram_m.size(); ++i){
        if( prog == postProgram_m[i])
            break;
    }
    active_postprogram = i;
    return postProgram_m[active_postprogram];
}

GLuint ShaderManager::setActivePostProg(const int& i){
    if( i >= 0 && i < postProgram_m.size()){
        active_postprogram = i;
    }
    return postProgram_m[active_postprogram];
}

unsigned int ShaderManager::postProgCount(){
    return postProgram_m.size();
}
