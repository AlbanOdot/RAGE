#ifndef MYMODEL_H
#define MYMODEL_H

#include "MyObject.h"
#include "./src/OpenGL/ShadersUtils/MyShaderProgram.h"
#include "./src/OpenGL/ShadersUtils/ShaderLoader.h"



//MyModel is the object to be displayed by the openGL
class MyModel : public MyObject
{
public:
    MyModel();

    MyModel(const std::string& meshPath);

    MyModel(const std::string& meshPath, const std::string& vsPath, const std::string& fsPath);

    MyModel(const std::string& meshPath, const std::string& vsPath, const std::string& tcPath,
            const std::string& tePath, const std::string& geoPath, const std::string& fsPath);

    //draw function wich display the object
    glm::mat4 getModel() { return _model; }
    GLuint getProg() { return _prog.getProgram(); }
private:
    // matrices
    glm::mat4 _model;
    MyShaderProgram _prog;
    ShaderLoader _loader;
    int _isProginit = 0;
    int _isSimpleProg = 0;
};

#endif // MYMODEL_H
