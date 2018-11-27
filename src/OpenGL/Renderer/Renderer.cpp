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
  initLighting();
  initSSAO();
  initHDR();
  initBloom();
  initFXAA();
  //MESH LOADING AND STORAGE
  m_objects.push_back(Model(filename));
  m_animation = false;
  //POSTPROCESS QUAD INIT
  m_postProcessScreen.quadLoad();
  //CAMERA STUFF
  _camera.reset(new TrackballCamera(glm::vec3(0.f, 0.f, 3.f)));
  _camera->setviewport(glm::vec4(0.f, 0.f, _width, _height));
  m_view = _camera->viewmatrix();
  m_projection = glm::perspective(_camera->zoom(), float(_width) / float(_height), 0.1f, 100.0f);
}

Renderer::Renderer(const int width, const int height, bool animation) : Scene(width, height), _camera(nullptr) {
  glCullFace(GL_FRONT_AND_BACK);
  resizeBuffers(2 * _width, 2 * _height);

  //PREPROCESS SHADER
  initPreprocess();
  //POSTPROCESS SHADERS
  initLighting();
  initSSAO();
  //MESH LOADING AND STORAGE
  m_objects.push_back(Model("../DataFiles/CylinderAnim.obj"));
  m_animation = true;
  //POSTPROCESS QUAD INIT
  m_postProcessScreen.quadLoad();
  //CAMERA STUFF
  _camera.reset(new TrackballCamera(glm::vec3(0.f, 0.f, 3.f)));
  _camera->setviewport(glm::vec4(0.f, 0.f, _width, _height));
  m_view = _camera->viewmatrix();
  m_projection = glm::perspective(_camera->zoom(), float(_width) / float(_height), 0.1f, 100.0f);
}

void Renderer::animationDraw(){

  glBindFramebuffer(GL_FRAMEBUFFER, 1);

  glClear(GL_COLOR_BUFFER_BIT);
  glClearColor(0.05f, 0.05f, 0.05f, 1.0f);
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
  glDisable(GL_DEPTH_TEST);

  glUseProgram(RENDERPROG);
  glActiveTexture(GL_TEXTURE0);
  glBindTexture(GL_TEXTURE_2D, m_GBuffer.position);
  glActiveTexture(GL_TEXTURE1);
  glBindTexture(GL_TEXTURE_2D, m_GBuffer.normal);
  glActiveTexture(GL_TEXTURE2);
  glBindTexture(GL_TEXTURE_2D, m_GBuffer.albedo);
  glActiveTexture(GL_TEXTURE3);
  glBindTexture(GL_TEXTURE_2D, ssaoBufferBlur.buf);

  glUniform1i(glGetUniformLocation(RENDERPROG, "position"), 0);
  glUniform1i(glGetUniformLocation(RENDERPROG, "normal"), 1);
  glUniform1i(glGetUniformLocation(RENDERPROG, "albedo"), 2);
  glUniform1i(glGetUniformLocation(RENDERPROG, "ssao"), 3);

  m_postProcessScreen.quadDraw();

}

void Renderer::draw(){
  //1ere passe de rendu
  //Qt utilise son propre buffer

  // QT use his own default frame buffer ...
  if (_drawfill)
    glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
  else
    glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);

  /* GBUFFER FILLING */
  m_GBuffer.bind();
  glClearColor(0.05f, 0.05f, 0.05f, 1.0f);
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
  glEnable(GL_DEPTH_TEST);

  glUseProgram(GBUFFERRENDER);
  glUniformMatrix4fv( glGetUniformLocation(GBUFFERRENDER, "view"), 1, GL_FALSE, glm::value_ptr(m_view));
  glUniformMatrix4fv( glGetUniformLocation(GBUFFERRENDER, "projection"), 1, GL_FALSE, glm::value_ptr(m_projection));
  m_view = _camera->viewmatrix();
  for(const auto& model : m_objects){
      glUniformMatrix4fv( glGetUniformLocation(GBUFFERRENDER, "model"), 1, GL_FALSE, glm::value_ptr(model.m_model));
      model.draw();
  }

  if(computeSSAO){
      ssaoBuffer.bind();
      glClear(GL_COLOR_BUFFER_BIT);
      glClearColor(0.00f, 0.0f, 0.0f, 1.0f);
      glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
      glEnable(GL_DEPTH_TEST);
      glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);

      glUseProgram(SSAO);
      glUniform3fv(glGetUniformLocation(SSAO,"kernel"), 64, ssaoKernel);
      glUniformMatrix4fv( glGetUniformLocation(SSAO, "projection"), 1, GL_FALSE, glm::value_ptr(m_projection));
      glActiveTexture(GL_TEXTURE0);
      glBindTexture(GL_TEXTURE_2D, m_GBuffer.position);
      glActiveTexture(GL_TEXTURE1);
      glBindTexture(GL_TEXTURE_2D, m_GBuffer.normal);
      glActiveTexture(GL_TEXTURE2);
      glBindTexture(GL_TEXTURE_2D, noiseTexture);
      glUniform1f(glGetUniformLocation(SSAO,"radius"), ssaoRadius);
      glUniform1f(glGetUniformLocation(SSAO,"bias"), ssaoBias);
      float noiseScale[2] ={static_cast<float>(_width/2.0),static_cast<float>(_height/2.0)};
      glUniform2fv(glGetUniformLocation(SSAO,"noiseScale"),1, noiseScale);
      m_postProcessScreen.quadDraw();

      ssaoBufferBlur.bind();
      glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
      glClearColor(1.f, 1.f, 1.f, 1.0f);
      glUseProgram(SSAOBLUR);
      glActiveTexture(GL_TEXTURE0);
      glBindTexture(GL_TEXTURE_2D,  ssaoBuffer.buf);
      m_postProcessScreen.quadDraw();
    }else{
      cout << "NO SSAO"<<endl;
      ssaoBuffer.bind();
      glClear(GL_COLOR_BUFFER_BIT);
      glClearColor(0.05f, 0.05f, 0.05f, 1.0f);
      glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
      ssaoBufferBlur.bind();
      glClearColor(1.f, 1.f, 1.f, 1.0f);
      glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    }

  if( m_animation){
      animationDraw();
      return;
    }
  cout << "C'est pas bon"<<endl;
  //2eme passe de rendu on combine G_BUFFER et ssaoBlur
  renderBuffer.bind();
  //glBindFramebuffer(GL_FRAMEBUFFER, 1);
  glClear(GL_COLOR_BUFFER_BIT);
  glClearColor(0.05f, 0.05f, 0.05f, 1.0f);
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
  glDisable(GL_DEPTH_TEST);
  glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
  glUseProgram(RENDERPROG);
  glActiveTexture(GL_TEXTURE0);
  glBindTexture(GL_TEXTURE_2D, m_GBuffer.position);
  glActiveTexture(GL_TEXTURE1);
  glBindTexture(GL_TEXTURE_2D, m_GBuffer.normal);
  glActiveTexture(GL_TEXTURE2);
  glBindTexture(GL_TEXTURE_2D, m_GBuffer.albedo);
  glActiveTexture(GL_TEXTURE3);
  glBindTexture(GL_TEXTURE_2D, ssaoBufferBlur.buf);
  glUniform1i(glGetUniformLocation(RENDERPROG, "position"), 0);
  glUniform1i(glGetUniformLocation(RENDERPROG, "normal"), 1);
  glUniform1i(glGetUniformLocation(RENDERPROG, "albedo"), 2);
  glUniform1i(glGetUniformLocation(RENDERPROG, "ssao"), 3);
  m_postProcessScreen.quadDraw();

  //FXAA
  fxaaBuffer.bind();
  //glBindFramebuffer(GL_FRAMEBUFFER, 1);
  glClearColor(0.05f, 0.05f, 0.05f, 1.0f);
  glDisable(GL_DEPTH_TEST);
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
  glUseProgram(FXAAPROG);
  glActiveTexture(GL_TEXTURE0);
  glBindTexture(GL_TEXTURE_2D,  renderBuffer.buf);
  glUniform1f(glGetUniformLocation(FXAAPROG,"minThreshold"),minThresholdFXAA);
  glUniform1f(glGetUniformLocation(FXAAPROG,"maxThreshold"),maxThresholdFXAA);
  glUniform1i(glGetUniformLocation(FXAAPROG, "showContour"),showContourFXAA);
  glUniform2fv(glGetUniformLocation(FXAAPROG, "inverseScreenSize"),1,invSS);
  glUniform1i(glGetUniformLocation(FXAAPROG, "computeFXAA"),computeFXAA);
  m_postProcessScreen.quadDraw();

  //BLOOM
  bloomBuffer.bind();
  glClearColor(0.05f, 0.05f, 0.05f, 1.0f);
  glDisable(GL_DEPTH_TEST);
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
  glUseProgram(BLOOMPROG);
  glActiveTexture(GL_TEXTURE0);
  glBindTexture(GL_TEXTURE_2D,  fxaaBuffer.buf);
  m_postProcessScreen.quadDraw();
  //BLUR
  //VERTICAL PASS
  blurBufferVert.bind();
  glClearColor(0.05f, 0.05f, 0.05f, 1.0f);
  glDisable(GL_DEPTH_TEST);
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
  glUseProgram(BLURPROG);
  glActiveTexture(GL_TEXTURE0);
  glBindTexture(GL_TEXTURE_2D,  bloomBuffer.buf);
  glUniform2fv(glGetUniformLocation(BLURPROG, "texelStep"),1,invSS);
  glUniform1f(glGetUniformLocation(BLURPROG, "horizontal"),0.);
  m_postProcessScreen.quadDraw();
  //HORIZONTAL PASS
  blurBufferHori.bind();
  glClearColor(0.05f, 0.05f, 0.05f, 1.0f);
  glDisable(GL_DEPTH_TEST);
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
  glActiveTexture(GL_TEXTURE0);
  glBindTexture(GL_TEXTURE_2D,  blurBufferVert.buf);
  glUniform2fv(glGetUniformLocation(BLURPROG, "texelStep"),1,invSS);
  glUniform1i(glGetUniformLocation(BLURPROG, "horizontal"),1.);
  m_postProcessScreen.quadDraw();


  //HDR
  glBindFramebuffer(GL_FRAMEBUFFER, 1);
  glClearColor(0.05f, 0.05f, 0.05f, 1.0f);
  glDisable(GL_DEPTH_TEST);
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
  glUseProgram(HDRPROG);
  glActiveTexture(GL_TEXTURE0);
  glBindTexture(GL_TEXTURE_2D,  blurBufferHori.buf);
  glActiveTexture(GL_TEXTURE1);
  glBindTexture(GL_TEXTURE_2D,  fxaaBuffer.buf);
  glUniform1i(glGetUniformLocation(HDRPROG,"screenTexture"),1);
  glUniform1i(glGetUniformLocation(HDRPROG,"brightTexture"),0);
  glUniform1f(glGetUniformLocation(HDRPROG, "gamma"),gammaHDR);
  glUniform1f(glGetUniformLocation(HDRPROG, "exposure"),exposureHDR);
  glUniform1f(glGetUniformLocation(HDRPROG, "BLOOM"),computeBLOOM ? 1.0 : 0.0);
  glUniform1i(glGetUniformLocation(HDRPROG,"computeHDR"),computeHDR);
  m_postProcessScreen.quadDraw();

}

void Renderer::initPreprocess(){
  m_GBuffer.init(2*_width,2*_height);
  char buff[1000];
  getcwd(buff,1000);
  std::string wd(buff);
  //PROCESS SHADERS
  std::string vshPath = wd +  std::string("/../src/OpenGL/Shader/Process/basic.vert.glsl");
  std::string GPath = wd +      std::string("/../src/OpenGL/Shader/Process/GBuffer.frag.glsl");
  //std::string GPath = wd +      std::string("/../src/OpenGL/Shader/Process/basic.frag.glsl");
  GBUFFERRENDER = programs.computeAddProgramm(vshPath,GPath);

}

void Renderer::initSSAO(){
  ssaoRadius = 0.5;
  ssaoBias = 0.01;
  std::uniform_real_distribution<GLfloat> randomFloats(0.0,1.0);
  std::default_random_engine  generator;
  for(unsigned int i = 0; i<63; ++i){
      glm::vec3 sample(randomFloats(generator) * 2.0 - 1.0, randomFloats(generator) * 2.0 - 1.0, randomFloats(generator));
      sample = glm::normalize(sample);
      sample *= randomFloats(generator);
      float scale = float(i) / 64.0;
      float scale2 = scale* scale;
      scale = 0.1f * scale2 + 1.0f*(1.0-scale2);
      sample *= scale;
      ssaoKernel[3*i]  = sample[0];
      ssaoKernel[3*i+1]= sample[1];
      ssaoKernel[3*i+3]= sample[2];
    }

  for(unsigned int i=0; i<15; i++){
      ssaoNoise[3*i] = randomFloats(generator) *2.0 - 1.0;
      ssaoNoise[3*i+1] = randomFloats(generator) * 2.0 -1.0;
      ssaoNoise[3*i+2] = 0.0;
    }

  glGenTextures(1, &noiseTexture);
  glBindTexture(GL_TEXTURE_2D,  noiseTexture);
  glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB32F, 4, 4, 0, GL_RGB, GL_FLOAT, ssaoNoise);
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
  SSAO = programs.computeAddPostProgramm(vshPath,SSAOPath);
  glUniform1i(glGetUniformLocation(SSAO, "position"), 0);
  glUniform1i(glGetUniformLocation(SSAO, "normal"), 1);
  glUniform1i(glGetUniformLocation(SSAO, "noise"), 2);
  SSAOBLUR = programs.computeAddPostProgramm(vshPath,SSAOBlur);
  glUniform1i(glGetUniformLocation(SSAOBLUR, "ssaoTexture"), 0);
  computeSSAO = true;

}

void Renderer::initLighting(){
  std::uniform_real_distribution<GLfloat> randompos(1.0,40.0);
  std::uniform_real_distribution<GLfloat> randomcol(0.0,2.0);
  std::default_random_engine  generator;
  std::vector<float> pos3 = {1.,1.,1., 1.,-1.,1., -1,0.,1};
  float LiColor[9] = {0.1,0.1,0.1, 0.1,0.1,0.1, 0.1,0.1,0.1};
  nbLights = 0;
  for(    ; nbLights<3; ++nbLights){
      glm::vec3 pos(pos3[3*nbLights], pos3[3*nbLights+1], pos3[3*nbLights+3]);
      pos = glm::normalize(pos);
      pos *= 50.;
      LiPosition[3*nbLights]  = pos[0];
      LiPosition[3*nbLights+1]= pos[1];
      LiPosition[3*nbLights+3]= pos[2];
    }
  std::cout << "The scene is composed of " << nbLights << "lights "<<std::endl;

  char buff[1000];
  getcwd(buff,1000);
  std::string wd(buff);
  std::string vshPath = wd +  std::string("/../src/OpenGL/Shader/PostProcess/pass.vert.glsl");
  std::string renderPath = wd + std::string("/../src/OpenGL/Shader/PostProcess/render.frag.glsl");
  RENDERPROG = programs.computeAddProgramm(vshPath,renderPath);
  glUniform1i(glGetUniformLocation(RENDERPROG, "position"), 0);
  glUniform1i(glGetUniformLocation(RENDERPROG, "normal"), 1);
  glUniform1i(glGetUniformLocation(RENDERPROG, "albedo"), 2);
  glUniform1i(glGetUniformLocation(RENDERPROG, "ssao"), 3);
  glUniform1i(glGetUniformLocation(RENDERPROG, "lightCount"), nbLights);
  glUniform3fv(glGetUniformLocation(RENDERPROG,"LiPosition"), nbLights, LiPosition);
  glUniform3fv(glGetUniformLocation(RENDERPROG,"LiColor"), nbLights, LiColor);

}

void Renderer::initHDR(){
  gammaHDR = 1.0;
  exposureHDR = 1.0;
  computeHDR = true;
  char buff[1000];
  getcwd(buff,1000);
  std::string wd(buff);
  std::string vshPath = wd +  std::string("/../src/OpenGL/Shader/PostProcess/pass.vert.glsl");
  std::string hdrPath = wd + std::string("/../src/OpenGL/Shader/PostProcess/hdr.frag.glsl");
  HDRPROG = programs.computeAddPostProgramm(vshPath,hdrPath);

}

void Renderer::initBloom(){
  computeBLOOM = true;
  char buff[1000];
  getcwd(buff,1000);
  std::string wd(buff);
  std::string vshPath = wd +  std::string("/../src/OpenGL/Shader/PostProcess/pass.vert.glsl");
  std::string bloomPath = wd + std::string("/../src/OpenGL/Shader/PostProcess/BLOOM.frag.glsl");
  std::string bloomBlurPath = wd + std::string("/../src/OpenGL/Shader/PostProcess/BLOOMBLUR.frag.glsl");
  BLOOMPROG = programs.computeAddPostProgramm(vshPath,bloomPath);
  glUniform1i(glGetUniformLocation(BLOOMPROG, "screenTexture"), 0);
  BLURPROG = programs.computeAddPostProgramm(vshPath,bloomBlurPath);
  glUniform1i(glGetUniformLocation(BLURPROG, "screenTexture"), 0);
  glUniform2fv(glGetUniformLocation(FXAAPROG, "inverseScreenSize"),1,invSS);
}

void Renderer::initFXAA(){
  showContourFXAA = false;
  computeFXAA = true;
  minThresholdFXAA = 0.0312;
  maxThresholdFXAA = 0.125;
  char buff[1000];
  getcwd(buff,1000);
  std::string wd(buff);
  std::string vshPath = wd +  std::string("/../src/OpenGL/Shader/PostProcess/pass.vert.glsl");
  std::string fxxPath = wd + std::string("/../src/OpenGL/Shader/PostProcess/FXAA.frag.glsl");
  FXAAPROG = programs.computeAddPostProgramm(vshPath,fxxPath);
  glUniform1i(glGetUniformLocation(FXAAPROG, "screenTexture"), 0);
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
  std::string OnOff;
  auto displayInfo = [&](){        std::cout << "******************************"<<std::endl;
      std::cout << "*     Post process status    *"<<std::endl;
      std::cout << "******************************"<<std::endl;
      OnOff = computeFXAA ? "[ON] " : "[OFF]";
      std::cout << "* FXAA :  " << OnOff <<"              *  min threshold : "<< minThresholdFXAA <<"     max threshold : "<<maxThresholdFXAA<<std::endl;
      OnOff = computeSSAO ? "[ON] " : "[OFF]";
      std::cout << "* SSAO :  " << OnOff <<"              *  radius : " <<ssaoRadius<<"    bias : "<< ssaoBias<<std::endl;
      OnOff = computeBLOOM ? "[ON] " : "[OFF]";
      std::cout << "* Bloom : " << OnOff <<"              *"<<std::endl;
      OnOff = computeHDR ? "[ON] " : "[OFF]";
      std::cout << "* HDR :   " << OnOff <<"              *  gamma : "<<gammaHDR<<"    exposure : "<<exposureHDR<<std::endl;
      std::cout << "******************************"<<std::endl;
      std::cout <<std::endl;
      std::cout <<std::endl;
      std::cout <<std::endl;};

  switch(k) {
    //TOOGLE OPTIONS - MAJ
    case 'E':
      computeBLOOM = !computeBLOOM;
      displayInfo();
      return true;
    case 'R':
      computeHDR = !computeHDR;
      displayInfo();
      return true;
    case '&':
      showContourFXAA = !showContourFXAA;
      computeFXAA = true;
      displayInfo();
      return true;
    case 'A':
      computeFXAA = !computeFXAA;
      showContourFXAA = false;
      displayInfo();
      return true;
    case 'Z':
      computeSSAO = !computeSSAO;
      displayInfo();
      return true;
      //###########FXAA###############
    case 'a':
      minThresholdFXAA = minThresholdFXAA - 0.01 > 0 ? minThresholdFXAA - 0.010 : 0.0;
      displayInfo();
      return true;
    case 'z':
      minThresholdFXAA = minThresholdFXAA + 0.01 < maxThresholdFXAA ? minThresholdFXAA + 0.01 : maxThresholdFXAA;
      displayInfo();
      return true;
    case 'q':
      maxThresholdFXAA = maxThresholdFXAA - 0.01 > minThresholdFXAA ? maxThresholdFXAA - 0.01 : minThresholdFXAA;
      displayInfo();
      return true;
    case 's':
      maxThresholdFXAA = maxThresholdFXAA + 0.01 < 0.5 ? maxThresholdFXAA + 0.01 : 0.5;
      displayInfo();
      return true;
      //##########SSAO##############
    case 'e':
      ssaoRadius = ssaoRadius - 0.05 > 0.f ? ssaoRadius - 0.05 : 0.0;
      displayInfo();
      return true;
    case 'r':
      ssaoRadius = ssaoRadius + 0.05 < 1.5 ? ssaoRadius + 0.05 : 1.5;
      displayInfo();
      return true;
    case 'd':
      ssaoBias = ssaoBias - 0.005 >0.0 ? ssaoBias - 0.005 : 0.0;
      displayInfo();
      return true;
    case 'f':
      ssaoBias = ssaoBias + 0.005 < 0.25 ? ssaoBias + 0.005 : 0.25;
      displayInfo();
      return true;
      //##############HDR+BLOOM##############
    case 'g':
      gammaHDR = gammaHDR - 0.1 < 0.0 ? 0. : gammaHDR- 0.1;
      displayInfo();
      return true;
    case 'h':
      gammaHDR = gammaHDR + 0.1 < 3. ? gammaHDR + 0.1 : 3.0;
      displayInfo();
      return true;
    case 't':
      exposureHDR = exposureHDR -0.1 < 0. ? 0.0 : exposureHDR - 0.1;
      displayInfo();
      return true;
    case 'y':
      exposureHDR = exposureHDR + 0.1 < 3. ? exposureHDR + 0.1 : 0.0;
      displayInfo();
      return true;
    default:
      return false;
    }

}

void Renderer::resizeBuffers(int w, int h){
  m_GBuffer.resize(w,h);
  ssaoBuffer.resize(w,h);
  ssaoBufferBlur.resize(w,h);
  renderBuffer.resize(w,h);
}

void Renderer::resize(int w, int h){
  resizeBuffers(w,h);
  Scene::resize(w, h);
  _camera->setviewport(glm::vec4(0.f, 0.f, _width, _height));
}
