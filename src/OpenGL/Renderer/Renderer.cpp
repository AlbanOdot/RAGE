#include <unistd.h>
#include "Renderer.h"
#include <iostream>
/*------------------------------------------------------------------------------------------------------------------------*/
/*------------------------------------------------------------------------------------------------------------------------*/
/*------------------------------------------------------------------------------------------------------------------------*/
/*------------------------------------------------------------------------------------------------------------------------*/
/*------------------------------------------------------------------------------------------------------------------------*/
/*------------------------------------------------------------------------------------------------------------------------*/

#define deg2rad(x) float(M_PI)*(x)/180.f

Renderer::Renderer(const int width, const int height, const std::string& filename) : Scene(width, height), _camera(nullptr) {
    glCullFace(GL_FRONT_AND_BACK);
    m_frameBuffer.init(2*width,2*height);
    //hardcoded init of the mesh
    //TODO here
    char buff[1000];
    getcwd(buff,1000);
    std::string wd(buff);
    //PROCESS SHADERS
    std::string vshPath = wd +  std::string("/../src/OpenGL/Shader/Process/basic.vert.glsl");
    std::string colorgPath = wd + std::string("/../src/OpenGL/Shader/Process/color.frag.glsl");
    std::string normalsPath = wd + std::string("/../src/OpenGL/Shader/Process/normals.frag.glsl");
    programs.computeAddProgramm(vshPath,colorgPath);
    programs.computeAddProgramm(vshPath,normalsPath);
    programs.setActiveProg(1);

    //POST PROCESS SHADERS
    vshPath = wd +  std::string("/../src/OpenGL/Shader/PostProcess/pass.vert.glsl");
    std::string SSAOPath = wd + std::string("/../src/OpenGL/Shader/PostProcess/SSAO.frag.glsl");
    std::string FXAAPath = wd + std::string("/../src/OpenGL/Shader/PostProcess/FXAA.frag.glsl");

    programs.computeAddPostProgramm(vshPath, FXAAPath);
    programs.setActivePostProg(0);

    //MESH LOADING AND STORAGE
    m_objects.push_back(MyObject(filename));

    //POSTPROCESS QUAD INIT
    m_postProcessScreen.quadLoad();

    //CAMERA STUFF
    _camera.reset(new TrackballCamera(glm::vec3(0.f, 0.f, 3.f)));
    _camera->setviewport(glm::vec4(0.f, 0.f, _width, _height));
    _view = _camera->viewmatrix();
    _projection = glm::perspective(_camera->zoom(), float(_width) / float(_height), 0.1f, 100.0f);
}

void Renderer::resize(int width, int height){
    Scene::resize(width, height);
    _camera->setviewport(glm::vec4(0.f, 0.f, _width, _height));
}

void Renderer::draw(){
    //1ere passe de rendu
    //Qt utilise son propre buffer

    // QT use his own default frame buffer ...
    GLint qt_buffer;
    glGetIntegerv(GL_FRAMEBUFFER_BINDING, &qt_buffer);

    /* ********************* Rendering ******************** */

    m_frameBuffer.bind();

    glClearColor(0.05f, 0.1f, 0.1f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glEnable(GL_DEPTH_TEST);

    if (!wireframe)
        glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
    else
        glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);

    programs.useProg();
    _view = _camera->viewmatrix();
    for(MyObject& obj : m_objects){
        glm::mat4 model(obj.getModel());
        glUniformMatrix4fv( glGetUniformLocation(programs.getActiveProg(), "model"), 1, GL_FALSE, glm::value_ptr(model));
        glUniformMatrix4fv( glGetUniformLocation(programs.getActiveProg(), "view"), 1, GL_FALSE, glm::value_ptr(_view));
        glUniformMatrix4fv( glGetUniformLocation(programs.getActiveProg(), "projection"), 1, GL_FALSE, glm::value_ptr(_projection));
        obj.draw();
    }

    //2eme passe de rendu, on vient rajouter les effets spéciaux
    glBindFramebuffer(GL_FRAMEBUFFER, qt_buffer);
    glClearColor(1,1,1, 1.0f);
    glDisable(GL_DEPTH_TEST);
    glClear(GL_COLOR_BUFFER_BIT );
    glUseProgram(programs.getActivePostProg());
    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, m_frameBuffer.textureColor);
    glUniform1i(glGetUniformLocation(programs.getActivePostProg(), "screenTexture"), 0);
    m_postProcessScreen.quadDraw();
}

void Renderer::mouseclick(int button, float xpos, float ypos) {
    _button = button;
    _mousex = xpos;
    _mousey = ypos;
    _camera->processmouseclick(_button, xpos, ypos);
}

void Renderer::mousemove(float xpos, float ypos) {
    _camera->processmousemovement(_button, xpos, ypos, true);
}

void Renderer::keyboardmove(int key, double time) {
    _camera->processkeyboard(Camera_Movement(key), time);
}

bool Renderer::keyboard(unsigned char k) {

    switch(k) {
    case '+':
        m_objects[0].subdivideLoop();
        draw();
        return true;
    case '*':
        //TODO Change this to something else
        m_objects[0].subdivideLoop();
        draw();
        return true;
    case '-':
        m_objects[0].edgeCollapse(m_objects[0].faceCount()/2);
        draw();
        return true;
    case '_':
        m_objects[0].halfEdgeCollapse(m_objects[0].faceCount()/2);
        draw();
        return true;
    case 'w':
        wireframe = !wireframe;
        draw();
        return true;
    default:
        return false;
    }
}
void Renderer::wheelEvent( const int down){
    _camera->processmousescroll(down);
    keyboard(';');
}
