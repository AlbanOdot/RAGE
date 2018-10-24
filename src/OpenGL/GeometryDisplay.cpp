#include <unistd.h>
#include "GeometryDisplay.h"
#include <iostream>
/*------------------------------------------------------------------------------------------------------------------------*/
/*------------------------------------------------------------------------------------------------------------------------*/
/*------------------------------------------------------------------------------------------------------------------------*/
/*------------------------------------------------------------------------------------------------------------------------*/
/*------------------------------------------------------------------------------------------------------------------------*/
/*------------------------------------------------------------------------------------------------------------------------*/

#define deg2rad(x) float(M_PI)*(x)/180.f

GeometryDisplay::GeometryDisplay(const int width, const int height) : Scene(width, height), _activecamera(0), _camera(nullptr) {
    glCullFace(GL_FRONT_AND_BACK);

    //hardcoded init of the mesh
    //TODO here
    char buff[1000];
    getcwd(buff,1000);
    std::string wd(buff);
    std::string meshPath = wd + std::string("/../src/OpenGL/DataFiles/Mesh/Skull.obj");
    std::string vshPath = wd + std::string("/../src/OpenGL/DataFiles/Shader/basic.vert.txt");
    std::string fragPath = wd + std::string("/../src/OpenGL/DataFiles/orange.frag.txt");

    _objects.emplace_back(MyModel(meshPath,  //MESH
                                  vshPath,   //Vertex Shader
                                  fragPath));//Fragment Shader
    _cameraselector.push_back( []()->Camera*{return new EulerCamera(glm::vec3(0.f, 0.f, 2.5));} );
    _cameraselector.push_back( []()->Camera*{return new TrackballCamera(glm::vec3(0.f, 0.f, 2.5),glm::vec3(0.f, 1.f, 0.f),glm::vec3(0.f, 0.f, 0.f));} );

    _camera.reset(_cameraselector[_activecamera]());

    _camera->setviewport(glm::vec4(0.f, 0.f, _width, _height));
    _view = _camera->viewmatrix();

    _projection = glm::perspective(_camera->zoom(), float(_width) / _height, 0.1f, 100.0f);
}

void GeometryDisplay::resize(int width, int height){
    Scene::resize(width, height);
    _camera->setviewport(glm::vec4(0.f, 0.f, _width, _height));
}

void GeometryDisplay::draw() {
    Scene::draw();
    _view = _camera->viewmatrix();

    GLuint prog = 0;
    prog = _objects[0].getProg();
    glUseProgram(prog);
    for( auto& obj : _objects){
        auto model = obj.getModel();
        obj.updateNormalMatrix(glm::mat3(model * _view));
        glUniformMatrix4fv( glGetUniformLocation(prog, "NormalMatrix"), 1, GL_FALSE, glm::value_ptr(obj.getNormalMatrix()));
        glUniformMatrix4fv( glGetUniformLocation(prog, "model"), 1, GL_FALSE, glm::value_ptr(model));
        obj.draw();
    }
    //We can do that since the camera is the same for all the programs
    glUniformMatrix4fv( glGetUniformLocation(prog, "view"), 1, GL_FALSE, glm::value_ptr(_view));
    glUniformMatrix4fv( glGetUniformLocation(prog, "projection"), 1, GL_FALSE, glm::value_ptr(_projection));
}

void GeometryDisplay::mouseclick(int button, float xpos, float ypos) {
    _button = button;
    _mousex = xpos;
    _mousey = ypos;
    _camera->processmouseclick(_button, xpos, ypos);
}

void GeometryDisplay::mousemove(float xpos, float ypos) {
    _camera->processmousemovement(_button, xpos, ypos, true);
}

void GeometryDisplay::keyboardmove(int key, double time) {
    _camera->processkeyboard(Camera_Movement(key), time);
}

bool GeometryDisplay::keyboard(unsigned char k) {

    switch(k) {
    case 'p':
        _activecamera = (_activecamera+1)%2;
        _camera.reset(_cameraselector[_activecamera]());
        _camera->setviewport(glm::vec4(0.f, 0.f, _width, _height));
        return true;
    default:
        return false;
    }
}
