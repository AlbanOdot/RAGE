#include <unistd.h>
#include "Renderer.h"
#include "src/OpenGL/Object/Shapes/Sphere.h"
#include "src/OpenGL/Object/Animation/Bone.h"
#include <random>
#include <iostream>
#include "../../Math/Algorithm.h"
#include <glm/gtx/quaternion.hpp>
#include "./src/Math/RayCast.h"
#include "glu.h"

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
  //MESH LOADING AND STORAGE
  m_objects.push_back(Model(filename));
  m_animation = false;
  //POSTPROCESS QUAD INIT
  m_postProcessScreen.quadLoad();
  //CAMERA STUFF
  _camera.reset(new TrackBall());
  _camera->resizeCamera(_width,_height);
  m_view = _camera->GetViewMatrix();
  m_projection = _camera->GetProjMatrix();
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
  //m_objects.push_back(Model("../DataFiles/CylinderAnim.obj"));

  m_bones.push_back(Bone(glm::vec3(1.0,.0,0.0),glm::vec3(1.0,.0,0.0)));
  m_bones[0].addChild(glm::vec3(1.0,1.0,0.0));
  /*m_bones[0].addChild(glm::vec3(-1,-1,0));
  std::deque<int> path = {1};
  m_bones[0].addChild(path);
  path = {1,0};
  m_bones[0].addChild(path);*/

  m_animation = true;
  //POSTPROCESS QUAD INIT
  m_postProcessScreen.quadLoad();
  //CAMERA STUFF
  _camera.reset(new TrackBall());
  _camera->resizeCamera(_width,_height);
  m_view = _camera->GetViewMatrix();
  m_projection = _camera->GetProjMatrix();
}

void Renderer::animationDraw(){



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
  m_view = _camera->GetViewMatrix();
  for(const auto& model : m_objects){
      glUniformMatrix4fv( glGetUniformLocation(GBUFFERRENDER, "model"), 1, GL_FALSE, glm::value_ptr(model.m_model));
      model.draw();
    }
  for(const auto& bone : m_bones){
      glUniformMatrix4fv( glGetUniformLocation(GBUFFERRENDER, "model"), 1, GL_FALSE, glm::value_ptr(bone.m_model));
      bone.draw();
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
      glBindTexture(GL_TEXTURE_2D, m_GBuffer.position());
      glActiveTexture(GL_TEXTURE1);
      glBindTexture(GL_TEXTURE_2D, m_GBuffer.normal());
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
      glBindTexture(GL_TEXTURE_2D,  ssaoBuffer.buffer());
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

  glBindFramebuffer(GL_FRAMEBUFFER, 1);

  glClear(GL_COLOR_BUFFER_BIT);
  glClearColor(0.05f, 0.05f, 0.05f, 1.0f);
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
  glDisable(GL_DEPTH_TEST);

  glUseProgram(RENDERPROG);
  glActiveTexture(GL_TEXTURE0);
  glBindTexture(GL_TEXTURE_2D, m_GBuffer.position());
  glActiveTexture(GL_TEXTURE1);
  glBindTexture(GL_TEXTURE_2D, m_GBuffer.normal());
  glActiveTexture(GL_TEXTURE2);
  glBindTexture(GL_TEXTURE_2D, m_GBuffer.albedo());
  glActiveTexture(GL_TEXTURE3);
  glBindTexture(GL_TEXTURE_2D, ssaoBufferBlur.buffer());

  glUniform1i(glGetUniformLocation(RENDERPROG, "position"), 0);
  glUniform1i(glGetUniformLocation(RENDERPROG, "normal"), 1);
  glUniform1i(glGetUniformLocation(RENDERPROG, "albedo"), 2);
  glUniform1i(glGetUniformLocation(RENDERPROG, "ssao"), 3);

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

void Renderer::wheelEvent( const int down){
  _camera->mouseScroll(down);
}

void Renderer::mouseclick(int button, float xpos, float ypos) {
  lastX[button] = xpos;
  lastY[button] = ypos;
  firstMouse[button] = false;
  m_last_button = button;
  if( button == LEFT_BUTTON){
      m_renderer_ray = _camera->getRayFromScreen(xpos,ypos);
      for(auto& bone : m_bones){
          if((m_clicked_bone = bone.clickOnSkeletton(m_renderer_ray)) != nullptr ){
              cout << "You clicked on bone : "<<m_clicked_bone->ID()<<endl;
            }
        }
    }
  //shortcut->mouseclick(button, xpos, ypos);
}

void Renderer::mousemove(float xpos, float ypos) {
  //TODO CALCUL DE ROTATION ICI
  //Boutton gauche
  //Rotation haut-bas autour de la fromCam -> BoneOrig
  //Rotation gauche-droit par rapport à l'axe direction x (fromCam Bone Orig)
  //Boutton droit
  //Pareil mais clamper dans la directionde plus grand angle
  float xOffset = xpos - lastX[m_last_button];
  float yOffset = lastY[m_last_button] - ypos;
  lastX[m_last_button] = xpos;
  lastY[m_last_button] = ypos;

  if(m_animation){
      switch(m_last_button){
        case RIGHT_BUTTON: break;
        case LEFT_BUTTON:
          if(m_clicked_bone) m_clicked_bone->rotate(2.f * (float)M_PI * xOffset * invSS[0],m_clicked_bone->origin() - _camera->m_position);
          break;
        case MIDDLE_BUTTON:break;
        case NO_BUTTON: break;
        }

    }else{
      _camera->mouseMovement(xOffset, yOffset, true);
    }

}

void Renderer::keyboardmove(int key, double time) {
  _camera->keyboard(Movement(key), time);
}

bool Renderer::keyboard(unsigned char k) {
  switch(k) {
    //TOOGLE OPTIONS - MAJ
    case 'S':
      computeSSAO = !computeSSAO;
      return true;
    case 'B':
      m_draw_aabb = !m_draw_aabb;
      setDrawAABB(m_draw_aabb);
      return true;
    case 'F':
      _camera->fitScene(m_objects);
      return true;
    case 'A':
      m_animation = !m_animation;
      return true;
      //##########SSAO##############
    case 'e':
      ssaoRadius = ssaoRadius - 0.05f > 0.f ? ssaoRadius - 0.05f : 0.0f;
      return true;
    case 'r':
      ssaoRadius = ssaoRadius + 0.05f < 1.5 ? ssaoRadius + 0.05f : 1.5f;
      return true;
    case 'd':
      ssaoBias = ssaoBias - 0.005f >0.0f ? ssaoBias - 0.005f : 0.0f;
      return true;
    case 'f':
      ssaoBias = ssaoBias + 0.005f < 0.25f ? ssaoBias + 0.005f : 0.25;
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
  _camera->resizeCamera(_width, _height);
}
