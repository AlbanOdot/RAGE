#include "MyModel.h"

unsigned int MyModel::currentProg = 0;
//All of the constructors
MyModel::MyModel(){}

MyModel::MyModel(const std::string& meshPath)
    : MyObject(meshPath), _isProginit(0),_isSimpleProg(0){
}

MyModel::MyModel(const std::string& meshPath, const std::string& vsPath, const std::string& fsPath)
    : MyObject(meshPath), _isProginit(1), _isSimpleProg(1){

    _loader = ShaderLoader(vsPath.c_str(),GL_VERTEX_SHADER,"VERTEX");
    GLuint vs = _loader.getShader();
    _loader = ShaderLoader(fsPath.c_str(),GL_FRAGMENT_SHADER,"FRAGMENT");
    GLuint fs = _loader.getShader();
    _prog.emplace_back(MyShaderProgram(vs,fs));

}

MyModel::MyModel(const std::string& meshPath, const std::string& vsPath, const std::string& tcPath,
        const std::string& tePath, const std::string& geoPath, const std::string& fsPath)
    : MyObject(meshPath),_isProginit(1), _isSimpleProg(0){
    _loader = ShaderLoader(vsPath.c_str(),GL_VERTEX_SHADER,"VERTEX");
    GLuint vs = _loader.getShader();
    _loader = ShaderLoader(tcPath.c_str(),GL_TESS_CONTROL_SHADER,"TESSCONTROL");
    GLuint tcs = _loader.getShader();
    _loader = ShaderLoader(tePath.c_str(),GL_TESS_EVALUATION_SHADER,"TESSEVAL");
    GLuint tes = _loader.getShader();
    _loader = ShaderLoader(geoPath.c_str(),GL_GEOMETRY_SHADER,"GEOMETRY");
    GLuint gs = _loader.getShader();
    _loader = ShaderLoader(fsPath.c_str(),GL_FRAGMENT_SHADER,"FRAGMENT");
    GLuint fs = _loader.getShader();
    _prog.emplace_back(MyShaderProgram(vs,tcs,tes,gs,fs));

}

void MyModel::draw(){
    if(!_isProginit) return;
    glBindVertexArray(vao);
    glDrawElements(GL_POINTS, indicesCount(), GL_UNSIGNED_INT, 0);
    glBindVertexArray(0);
}
