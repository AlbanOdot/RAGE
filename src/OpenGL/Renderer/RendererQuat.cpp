#include <unistd.h>
#include "RendererQuat.h"
#include "src/OpenGL/Object/Shapes/Sphere.h"
#include "src/OpenGL/Object/Animation/Bone.h"
#include <random>
#include <iostream>
#include "../../Math/Algorithm.h"
#include "../../Math/distance.h"
#include <glm/gtx/quaternion.hpp>
#include "./src/Math/RayCast.h"
#include "glu.h"
#include "./src/Math/DualQuaternion.h"
#include "./src/Math/Quaternion.h"

#define GL_SILENCE_DEPRECATION 1
/*------------------------------------------------------------------------------------------------------------------------*/
/*------------------------------------------------------------------------------------------------------------------------*/
/*------------------------------------------------------------------------------------------------------------------------*/
/*------------------------------------------------------------------------------------------------------------------------*/
/*------------------------------------------------------------------------------------------------------------------------*/
/*------------------------------------------------------------------------------------------------------------------------*/

#define deg2rad(x) float(M_PI)*(x)/180.f

RendererQuat::RendererQuat(const int width, const int height, const std::string& filename) : Scene(width, height), _camera(nullptr) {
  glCullFace(GL_FRONT_AND_BACK);
  resizeBuffers(2 * _width, 2 * _height);

  //PREPROCESS SHADER
  initPreprocess();
  //POSTPROCESS SHADERS
  initLighting();
  initSSAO();
  //MESH LOADING AND STORAGE
  m_objects.push_back(BasicModel(filename));
  m_animation = false;
  //POSTPROCESS QUAD INIT
  m_postProcessScreen.quadLoad();
  //CAMERA STUFF
  _camera.reset(new TrackBall());
  _camera->resizeCamera(_width,_height);
  m_view = _camera->GetViewMatrix();
  m_projection = _camera->GetProjMatrix();
}

RendererQuat::RendererQuat(const int width, const int height, bool animation) : Scene(width, height), m_clicked_bone(nullptr),_camera(nullptr) {
  glCullFace(GL_FRONT_AND_BACK);
  resizeBuffers(2 * _width, 2 * _height);

  //PREPROCESS SHADER
  initPreprocess();
  //POSTPROCESS SHADERS
  initLighting();
  initSSAO();

  //MESH LOADING AND STORAGE

  //Shapes

  //Basic Model
  //m_objects.emplace_back(BasicModel("../DataFiles/smoothCyl.obj"));

  //Animated Model
  m_animated_objects.emplace_back(AnimatedModel(Cylinder(glm::vec3(-2,0,0),glm::vec3(1,0,0),4.0)));
  //m_animated_objects.emplace_back(AnimatedModel(std::string("../DataFiles/Hand.obj")));
  Bone skeletton1(glm::vec3(-2.f,.0,.0),glm::vec3(1.0,.0,0.0));
  Bone son = skeletton1.addChild(glm::vec3(1.0,0,0.0));
  //TODO Voir pourquoi on a que 2 os qui s'affichent.
  //son.addChild(glm::vec3(1.0,-1,0.0));
  m_animated_objects[0].attachSkeletton(skeletton1);
  m_animation = true;

  //POSTPROCESS QUAD INIT
  m_postProcessScreen.quadLoad();
  //CAMERA STUFF
  _camera.reset(new TrackBall());
  _camera->resizeCamera(_width,_height);
  m_view = _camera->GetViewMatrix();
  m_projection = _camera->GetProjMatrix();
  (void)animation;
}

void RendererQuat::draw(){
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
      glUniform1i(glGetUniformLocation(GBUFFERRENDER, "animated"), 0);
      glUniformMatrix4fv( glGetUniformLocation(GBUFFERRENDER, "models"), 1, GL_FALSE,glm::value_ptr(model.model()));
      model.draw();
    }
  for(auto& animated_model : m_animated_objects){
      //Draw the object
      glUniform1i(glGetUniformLocation(GBUFFERRENDER, "animated"), 1);
      glUniformMatrix4fv( glGetUniformLocation(GBUFFERRENDER, "models"), 1, GL_FALSE,glm::value_ptr(animated_model.model()));
      animated_model.draw();

      //Draw the bones
      /*glDisable(GL_DEPTH_TEST);
      for(const auto& bone : animated_model.skeletton().boneList()){
          glUniform1i(glGetUniformLocation(GBUFFERRENDER, "animated"), 0);
          glUniformMatrix4fv( glGetUniformLocation(GBUFFERRENDER, "models"), 1, GL_FALSE,glm::value_ptr(bone->model()));
          bone->draw();
        }*/
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

void RendererQuat::initPreprocess(){
  m_GBuffer.init(2*_width,2*_height);
  char buff[1000];
  getcwd(buff,1000);
  std::string wd(buff);
  //PROCESS SHADERS
  std::string vshPath = wd +  std::string("/../src/OpenGL/Shader/Process/basic.vert.glsl");
  std::string GPath = wd +      std::string("/../src/OpenGL/Shader/Process/GBuffer.frag.glsl");
  GBUFFERRENDER = programs.computeAddProgramm(vshPath,GPath);

}

void RendererQuat::initSSAO(){
  ssaoRadius = 0.5f;
  ssaoBias = 0.01f;
  std::uniform_real_distribution<GLfloat> randomFloats(0.0,1.0);
  std::default_random_engine  generator;
  for(unsigned int i = 0; i<63; ++i){
      glm::vec3 sample(randomFloats(generator) * 2.0f- 1.0f, randomFloats(generator) * 2.0f - 1.0f, randomFloats(generator));
      sample = glm::normalize(sample);
      sample *= randomFloats(generator);
      float scale = float(i) / 64.0f;
      float scale2 = scale* scale;
      scale = 0.1f * scale2 + 1.0f*(1.0f-scale2);
      sample *= scale;
      ssaoKernel[3*i]  = sample[0];
      ssaoKernel[3*i+1]= sample[1];
      ssaoKernel[3*i+3]= sample[2];
    }

  for(unsigned int i=0; i<15; i++){
      ssaoNoise[3*i] = randomFloats(generator) *2.0f - 1.0f;
      ssaoNoise[3*i+1] = randomFloats(generator) * 2.0f -1.0f;
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

void RendererQuat::initLighting(){
  std::uniform_real_distribution<GLfloat> randompos(1.0f,40.0f);
  std::uniform_real_distribution<GLfloat> randomcol(0.0f,2.0f);
  std::default_random_engine  generator;
  std::vector<float> pos3 = {1.f,1.f,1.f, 1.f,-1.f,1.f, -1.f,0.f,1.f};
  float LiColor[9] = {0.1f,0.1f,0.1f, 0.1f,0.1f,0.1f, 0.1f,0.1f,0.1f};
  nbLights = 0;
  for(    ; nbLights<3; ++nbLights){
      glm::vec3 pos(pos3[3*nbLights], pos3[3*nbLights+1], pos3[3*nbLights+3]);
      pos = glm::normalize(pos);
      pos *= 50.f;
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

void RendererQuat::wheelEvent( const int down){
  _camera->mouseScroll(down);
}

void RendererQuat::mouseclick(int button, float xpos, float ypos) {
  lastX[button] = xpos;
  lastY[button] = ypos;
  firstMouse[button] = false;
  m_last_button = button;
  if( button == LEFT_BUTTON){
      m_RendererQuat_ray = _camera->getRayFromScreen(xpos,ypos);
      for(auto& anim_obj : m_animated_objects){
          for( auto& bone : anim_obj.skeletton().boneList()){
              if((m_clicked_bone = bone->clickOnSkeletton(m_RendererQuat_ray)) != nullptr ){
                  cout << "You clicked on bone : "<<m_clicked_bone->ID()<<endl;
                  break;
                }
            }
        }
    }
  //shortcut->mouseclick(button, xpos, ypos);
}

void RendererQuat::mousemove(float xpos, float ypos) {
  float xOffset = xpos - lastX[m_last_button];
  float yOffset = lastY[m_last_button] - ypos;
  lastX[m_last_button] = xpos;
  lastY[m_last_button] = ypos;

  if(m_animation){
      switch(m_last_button){
        case RIGHT_BUTTON:
          if(m_clicked_bone != nullptr){
              glm::mat4 model = m_clicked_bone->model();
              float offset = yOffset > xOffset ? yOffset : xOffset;
              glm::vec4 axis = yOffset > xOffset ? glm::vec4(0,0,1,0) : glm::vec4(0,1,0,0);
              Math::DualQuaternion dq(Math::Quaternion(m_view * model * axis,2.f * (float)M_PI * offset * invSS[0]),m_clicked_bone->origin());
              m_clicked_bone->rotate(dq);
               m_clicked_bone->rotate(2.f * (float)M_PI * offset * invSS[0], m_view * model * axis);//For the display
              for(auto& amod : m_animated_objects)
                amod.applyBonesTransformationQuat();
            }
          break;
        case LEFT_BUTTON:

          if(m_clicked_bone != nullptr){
              glm::mat4 model = m_clicked_bone->model();
              glm::vec3 ZCamAxis = m_view * model * glm::vec4(0,0,1,0);
              glm::vec3 XCamAxis = m_view * model * glm::vec4(0,1,0,0);
              Math::DualQuaternion dqy(Math::Quaternion(ZCamAxis,2.f * (float)M_PI * yOffset * invSS[0]),m_clicked_bone->origin());
              Math::DualQuaternion dqx(Math::Quaternion(XCamAxis,2.f * (float)M_PI * xOffset * invSS[1]),m_clicked_bone->origin());
              m_clicked_bone->rotate(dqy);
              m_clicked_bone->rotate(dqx);
              m_clicked_bone->rotate(2.f * (float)M_PI * yOffset * invSS[0],ZCamAxis);
              m_clicked_bone->rotate(2.f * (float)M_PI * xOffset * invSS[0],XCamAxis);
              for(auto& amod : m_animated_objects)
                amod.applyBonesTransformationQuat();
            }
          break;
        case MIDDLE_BUTTON:break;
        case NO_BUTTON: break;
        }

    }else{
      _camera->mouseMovement(xOffset, yOffset, true);
    }

}

void RendererQuat::keyboardmove(int key, double time) {
  _camera->keyboard(Movement(key), time);
}

bool RendererQuat::keyboard(unsigned char k) {
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
      ssaoRadius = ssaoRadius + 0.05f < 1.5f ? ssaoRadius + 0.05f : 1.5f;
      return true;
    case 'd':
      ssaoBias = ssaoBias - 0.005f >0.0f ? ssaoBias - 0.005f : 0.0f;
      return true;
    case 'f':
      ssaoBias = ssaoBias + 0.005f < 0.25f ? ssaoBias + 0.005f : 0.25f;
      return true;
      //#######Bone#########
    case 'c':
      if( m_clicked_bone != nullptr)
        m_clicked_bone->addChild();
      cout << "add child"<<endl;
      return true;
      //#######Weights#######
    case '+':
      weightTresholdUp(true);
      return true;
    case '-':
      weightTresholdUp(false);
      return true;
    default:
      return false;
    }
  return false;
}

void RendererQuat::resizeBuffers(int w, int h){
  m_GBuffer.resize(w,h);
  ssaoBuffer.resize(w,h);
  ssaoBufferBlur.resize(w,h);
  renderBuffer.resize(w,h);
}

void RendererQuat::resize(int w, int h){
  resizeBuffers(w,h);
  Scene::resize(w, h);
  _camera->resizeCamera(_width, _height);
}

void RendererQuat::setDrawAABB(bool d)
{
  for(auto& model : m_objects){
      model.displayAABB(d);
    }
  for(auto& anim_obj : m_animated_objects){
      anim_obj.displayAABB(d);
    }

}

void RendererQuat::weightTresholdUp(bool up){
  for(auto& anim_obj : m_animated_objects){
      anim_obj.tresholdUp(up);
    }
}
