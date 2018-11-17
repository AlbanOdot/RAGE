#include <unistd.h>
#include "Renderer.h"
#include <random>
#include <iostream>
#define GL_SILENCE_DEPRECATION 1
/*------------------------------------------------------------------------------------------------------------------------*/
/*------------------------------------------------------------------------------------------------------------------------*/
/*------------------------------------------------------------------------------------------------------------------------*/
/*------------------------------------------------------------------------------------------------------------------------*/
/*------------------------------------------------------------------------------------------------------------------------*/
/*------------------------------------------------------------------------------------------------------------------------*/

#define deg2rad(x) float(M_PI)*(x)/180.f

Renderer::Renderer(const int width, const int height, const std::string& filename) : Scene(width, height), _camera(nullptr) {
    glCullFace(GL_FRONT_AND_BACK);
    resizeBuffers(2 * _width, 2 * _height);

    //PREPROCESS SHADER
    initPreprocess();

    //POSTPROCESS SHADERS
    initSSAO();
    initHDR();
    initBloom();
    initBloomBlur();
    initFXAA();
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

void Renderer::draw(){
    //1ere passe de rendu
    //Qt utilise son propre buffer

    // QT use his own default frame buffer ...
    GLint qt_buffer;
    glGetIntegerv(GL_FRAMEBUFFER_BINDING, &qt_buffer);

    /* ********************* Rendering ******************** */

    m_GBuffer.bind();

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

    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, m_GBuffer.position);
    glActiveTexture(GL_TEXTURE1);
    glBindTexture(GL_TEXTURE_2D, m_GBuffer.normal);
    glActiveTexture(GL_TEXTURE2);
    glBindTexture(GL_TEXTURE_2D, m_GBuffer.albedo);
    //SSAO

    if(computeSSAO){
        ssaoBuffer.bind();
        glClear(GL_COLOR_BUFFER_BIT);
        glClearColor(0.05f, 0.5f, 0.5f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        glEnable(GL_DEPTH_TEST);
        glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);

        programs.usePostProg(ShaderManager::SSAO);
        GLint location = glGetUniformLocation(programs.get(ShaderManager::SSAO),"kernel");
        glUniform3fv(location, 64, ssaoKernel);
        glUniformMatrix4fv( glGetUniformLocation(programs.getActiveProg(), "projection"), 1, GL_FALSE, glm::value_ptr(_projection));
        glActiveTexture(GL_TEXTURE0);
        glBindTexture(GL_TEXTURE_2D, m_GBuffer.position);
        glActiveTexture(GL_TEXTURE1);
        glBindTexture(GL_TEXTURE_2D, m_GBuffer.normal);
        glActiveTexture(GL_TEXTURE2);
        glBindTexture(GL_TEXTURE_2D,  noiseTexture);
        glUniform1f(glGetUniformLocation(programs.getActivePostProg(),"radius"), ssaoRadius);
        glUniform1f(glGetUniformLocation(programs.getActivePostProg(),"bias"), ssaoBias);
        float noiseScale[2] ={static_cast<float>(_width/4.0),static_cast<float>(_height/4.0)};
        glUniform2fv(glGetUniformLocation(programs.getActivePostProg(),"noiseScale"),1, noiseScale);
        m_postProcessScreen.quadDraw();
/*
        ssaoBufferBlur.bind();
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        programs.usePostProg(ShaderManager::SSAOBLUR);
        glActiveTexture(GL_TEXTURE0);
        glBindTexture(GL_TEXTURE_2D,  ssaoBufferBlur.buf);
        m_postProcessScreen.quadDraw();*/
    }





    //BLOOM


    //HDR




    //FXAA



    //LAST PROCESS DRAW SCREEN
    glBindFramebuffer(GL_FRAMEBUFFER, qt_buffer);
    glClearColor(1,1,1, 1.0f);
    glDisable(GL_DEPTH_TEST);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    programs.setActivePostProg(2);
    programs.usePostProg();
    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D,  ssaoBuffer.buf);
    glUniform1i(glGetUniformLocation(programs.getActivePostProg(), "screenTexture"), 2);
    glUniform1f(glGetUniformLocation(programs.getActivePostProg(),"minThreshold"),minThresholdFXAA);
    glUniform1f(glGetUniformLocation(programs.getActivePostProg(),"maxThreshold"),maxThresholdFXAA);
    glUniform2fv(glGetUniformLocation(programs.getActivePostProg(), "inverseScreenSize"),1,invSS);
    glUniform1i(glGetUniformLocation(programs.getActivePostProg(), "showContour"),showContour);
    glUniform1i(glGetUniformLocation(programs.getActivePostProg(), "computeFXAA"),computeFXAA);

    m_postProcessScreen.quadDraw();
}

void Renderer::initPreprocess(){
    m_GBuffer.init(2*_width,2*_height);
    char buff[1000];
    getcwd(buff,1000);
    std::string wd(buff);
    //PROCESS SHADERS
    std::string vshPath = wd +  std::string("/../src/OpenGL/Shader/Process/basic.vert.glsl");
    std::string GPath = wd + std::string("/../src/OpenGL/Shader/Process/GBuffer.frag.glsl");
    programs.computeAddProgramm(vshPath,GPath);
    programs.setActiveProg(ShaderManager::GBUFFER);
}
void Renderer::initSSAO(){
    std::uniform_real_distribution<GLfloat> randomFloats(0.0,1.0);
    std::default_random_engine  generator;
    for(unsigned int i = 0; i<64; ++i){
        glm::vec3 sample(randomFloats(generator) * 2.0 - 1.0, randomFloats(generator) * 2.0 - 1.0, randomFloats(generator));
        sample = glm::normalize(sample);
        sample *= randomFloats(generator);
        float scale = float(i) / 64.0;
        float scale2 = scale* scale;
        scale = 0.1f * (1.0 - scale2) + 1.0f*scale2;
        sample *= scale;
        ssaoKernel[3*i]  = sample[0];
        ssaoKernel[3*i+1]= sample[1];
        ssaoKernel[3*i+3]= sample[2];
    }

    for(unsigned int i=0; i<16; i++){
        ssaoNoise[3*i] = randomFloats(generator) *2.0 - 1.0;
        ssaoNoise[3*i+1] = randomFloats(generator) * 2.0 -1.0;
        ssaoNoise[3*i+2] = 0.0;
    }

    glGenTextures(1, &noiseTexture);
    glBindTexture(GL_TEXTURE_2D,  noiseTexture);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB32F, 4, 4, 0, GL_RGB, GL_FLOAT, &ssaoNoise[0]);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

    char buff[1000];
    getcwd(buff,1000);
    std::string wd(buff);
    std::string vshPath = wd +  std::string("/../src/OpenGL/Shader/PostProcess/pass.vert.glsl");
    std::string SSAOPath = wd + std::string("/../src/OpenGL/Shader/PostProcess/SSAO.frag.glsl");
    std::string SSAOBlur = wd + std::string("/../src/OpenGL/Shader/PostProcess/SSAOBLUR.frag.glsl");
    programs.computeAddPostProgramm(vshPath,SSAOPath);
    programs.usePostProg(ShaderManager::SSAO);
    glUniform1i(glGetUniformLocation(programs.getActivePostProg(), "position"), 0);
    glUniform1i(glGetUniformLocation(programs.getActivePostProg(), "normal"), 1);
    glUniform1i(glGetUniformLocation(programs.getActivePostProg(), "noise"), 2);

    programs.computeAddPostProgramm(vshPath,SSAOBlur);
    programs.usePostProg(ShaderManager::SSAOBLUR);
    glUniform1i(glGetUniformLocation(programs.getActivePostProg(), "ssaoTexture"), 0);

    computeSSAO = true;

}
void Renderer::initHDR(){
    char buff[1000];
    getcwd(buff,1000);
    std::string wd(buff);
    std::string vshPath = wd +  std::string("/../src/OpenGL/Shader/PostProcess/pass.vert.glsl");
    std::string FXAAPath = wd + std::string("/../src/OpenGL/Shader/PostProcess/FXAA.frag.glsl");
}
void Renderer::initBloom(){
    char buff[1000];
    getcwd(buff,1000);
    std::string wd(buff);
    std::string vshPath = wd +  std::string("/../src/OpenGL/Shader/PostProcess/pass.vert.glsl");

}
void Renderer::initBloomBlur(){
    char buff[1000];
    getcwd(buff,1000);
    std::string wd(buff);
    std::string vshPath = wd +  std::string("/../src/OpenGL/Shader/PostProcess/pass.vert.glsl");

}
void Renderer::initFXAA(){
    showContour = false;
    computeFXAA = true;
    minThresholdFXAA = 0.0312;
    maxThresholdFXAA = 0.125;



    char buff[1000];
    getcwd(buff,1000);
    std::string wd(buff);
    std::string vshPath = wd +  std::string("/../src/OpenGL/Shader/PostProcess/pass.vert.glsl");
    std::string fxxPath = wd + std::string("/../src/OpenGL/Shader/PostProcess/FXAA.frag.glsl");
    GLuint fxaa = programs.computeAddPostProgramm(vshPath,fxxPath);
}


void Renderer::wheelEvent( const int down){
    _camera->processmousescroll(down);
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
        //###########FXAA###############
    case 'f':
        showContour = !showContour;
        computeFXAA = true;
        return true;
    case 'F':
        computeFXAA = !computeFXAA;
        showContour = false;
        return true;
    case 'd':
        minThresholdFXAA = minThresholdFXAA - 0.01 > 0 ? minThresholdFXAA - 0.010 : 0;
        std::cout << "minThreshhold down to "<< minThresholdFXAA <<std::endl;
        return true;
    case 'g':
        minThresholdFXAA = minThresholdFXAA + 0.01 < maxThresholdFXAA ? minThresholdFXAA + 0.01 : maxThresholdFXAA;
        std::cout << "minThreshhold up to "<< minThresholdFXAA <<std::endl;
        return true;
    case 'D':
        maxThresholdFXAA = maxThresholdFXAA - 0.01 > minThresholdFXAA ? maxThresholdFXAA - 0.01 : minThresholdFXAA;
        std::cout << "maxThreshhold down to "<< maxThresholdFXAA <<std::endl;
        return true;
    case 'G':
        maxThresholdFXAA = maxThresholdFXAA + 0.01 < 0.5 ? maxThresholdFXAA + 0.01 : 0.5;
        std::cout << "maxThreshhold up to "<< maxThresholdFXAA <<std::endl;
        return true;
    default:
        return false;
    }
}


void Renderer::resizeBuffers(int w, int h){
    m_GBuffer.resize(w,h);
    ssaoBuffer.resize(w,h);
    ssaoBufferBlur.resize(w,h);
    fxaaBuffer.resize(w,h);
    hdrBuffer.resize(w,h);
    bloomBuffer.resize(w,h);
    pingpongBuffers[0].resize(w,h);
    pingpongBuffers[1].resize(w,h);
}

void Renderer::resize(int w, int h){
    resizeBuffers(w,h);
    Scene::resize(w, h);
    _camera->setviewport(glm::vec4(0.f, 0.f, _width, _height));
}
