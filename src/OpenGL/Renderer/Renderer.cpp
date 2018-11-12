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
    m_frameBuffer.init(width,height);
    //hardcoded init of the mesh
    //TODO here
    char buff[1000];
    getcwd(buff,1000);
    std::string wd(buff);
    std::string vshPath = wd +  std::string("/../src/OpenGL/Shader/basic.vert.txt");
    std::string fragPath = wd + std::string("/../src/OpenGL/Shader/normals.frag.txt");

    m_object = MyModel(filename,  //MESH
                       vshPath,   //Vertex Shader
                       fragPath);//Fragment Shader

    std::string meshPath = wd + std::string("/../DataFiles/Mesh/square.obj");
    vshPath = wd +  std::string("/../src/OpenGL/Shader/pass.vert.txt");
    fragPath = wd + std::string("/../src/OpenGL/Shader/SSAO.frag.txt");
    m_postProcessScreen = MyModel(meshPath, vshPath, fragPath);

    _camera.reset(new TrackballCamera(glm::vec3(0.f, 0.f, 3.f)));
    _camera->setviewport(glm::vec4(0.f, 0.f, _width, _height));
    _view = _camera->viewmatrix();
    _projection = glm::perspective(_camera->zoom(), float(_width) / float(_height), 0.1f, 100.0f);
}

void Renderer::resize(int width, int height){
    Scene::resize(width, height);
    _camera->setviewport(glm::vec4(0.f, 0.f, _width, _height));
}

/*void Renderer::draw() {
    //1ere passe de rendu
    //Qt utilise son propre buffer
    GLint qt_buffer;
    glGetIntegerv(GL_FRAMEBUFFER_BINDING, &qt_buffer);
    std::cout << "Qt buffer idx : "<<qt_buffer<<std::endl;
    // first pass
    m_frameBuffer.bind();
    //glClearColor(0.3f, 0.3f, 0.3f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); // we're not using the stencil buffer now
    glEnable(GL_DEPTH_TEST);

    if( wireframe )
        glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
    else
        glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);

    glUseProgram(m_object.getProg());
    _view = _camera->viewmatrix();
    glm::mat4 model(m_object.getModel());
    glUniformMatrix4fv( glGetUniformLocation(m_object.getProg(), "model"), 1, GL_FALSE, glm::value_ptr(model));
    glUniformMatrix4fv( glGetUniformLocation(m_object.getProg(), "view"), 1, GL_FALSE, glm::value_ptr(_view));
    glUniformMatrix4fv( glGetUniformLocation(m_object.getProg(), "projection"), 1, GL_FALSE, glm::value_ptr(_projection));
    m_object.draw();

    //2eme passe de rendu, on vient rajouter les effets spéciaux
    //On rebind la bonne sortie (qt opengl widget )
    glBindFramebuffer(GL_FRAMEBUFFER, 1);
    glClearColor(0.3,0.3,0.3, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT);
    glUseProgram(m_postProcessScreen.getProg());
    glActiveTexture(GL_TEXTURE0);
    glDisable(GL_DEPTH_TEST);
    glBindTexture(GL_TEXTURE_2D, m_frameBuffer.textureColor);
    glUniform1i(glGetUniformLocation(m_postProcessScreen.getProg(), "screenTexture"), 0);
    m_postProcessScreen.draw();

}*/
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

    glUseProgram(m_object.getProg());
    _view = _camera->viewmatrix();
    glm::mat4 model(m_object.getModel());
    glUniformMatrix4fv( glGetUniformLocation(m_object.getProg(), "model"), 1, GL_FALSE, glm::value_ptr(model));
    glUniformMatrix4fv( glGetUniformLocation(m_object.getProg(), "view"), 1, GL_FALSE, glm::value_ptr(_view));
    glUniformMatrix4fv( glGetUniformLocation(m_object.getProg(), "projection"), 1, GL_FALSE, glm::value_ptr(_projection));
    m_object.draw();

    //2eme passe de rendu, on vient rajouter les effets spéciaux
    glBindFramebuffer(GL_FRAMEBUFFER, qt_buffer);
    glClearColor(1,1,1, 1.0f);
    glDisable(GL_DEPTH_TEST);
    glClear(GL_COLOR_BUFFER_BIT );
    glUseProgram(m_postProcessScreen.getProg());
    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, m_frameBuffer.textureColor);
    glUniform1i(glGetUniformLocation(m_postProcessScreen.getProg(), "screenTexture"), 0);
    m_postProcessScreen.draw();
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
        m_object.subdivideLoop();
        draw();
        return true;
    case '*':
        //TODO Change this to something else
        m_object.subdivideLoop();
        draw();
        return true;
    case '-':
        m_object.edgeCollapse(m_object.faceCount()/2);
        draw();
        return true;
    case '_':
        m_object.halfEdgeCollapse(m_object.faceCount()/2);
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
