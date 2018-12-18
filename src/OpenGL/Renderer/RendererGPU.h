#ifndef RendererGPUGPU_H
#define RendererGPUGPU_H

#include "scene.h"

#include "../Camera/TrackBall.hpp"
#include "../Buffers/FrameBuffers/RGBbuffer.h"
#include "../Buffers/FrameBuffers/GBuffer.h"
#include "../Buffers/FrameBuffers/RedBuffer.h"
#include "../Buffers/FrameBuffers/Textures/RedTexture.h"
#include "../Object/Model/BasicModel.h"
#include "../Object/Model/ShapeModel.h"
#include "../Object/Animation/AnimatedModel.h"
#include "../ShadersUtils/shadermanager.h"
#include "../Object/Animation/Bone.h"

#include <memory>
#include <functional>

class RendererGPU : public Scene
{
public:
  RendererGPU(const int width, const int height,const std::string& filename);
  RendererGPU(const int width, const int height) : Scene(width,height){}
  RendererGPU(const int width, const int height, int metrique, int model);

  void resize(int width, int height) override;
  void draw() override;

  void mouseclick(int button, float xpos, float ypos) override;
  void mousemove(float xpos, float ypos) override;
  void keyboardmove(int key, double time) override;
  bool keyboard(unsigned char k) override;
  void wheelEvent( const int down) override;
  void resizeBuffers(int w, int h);


  //INIT
  void initPreprocess();
  void initSSAO();
  void initLighting();

private:

  //Change this to vector if you need multiple objects
  std::vector<BasicModel> m_objects;
  std::vector<ShapeModel> m_shapes;
  std::vector<AnimatedModel> m_animated_objects;
  std::vector<Bone> m_bones;

  Bone* m_clicked_bone;

  Ray m_RendererGPU_ray;

  //PostProcess stuff
  GLuint RENDERPROG;
  GLuint GBUFFERRENDER;
  Quad m_postProcessScreen;
  GBuffer m_GBuffer;
  RGBBuffer renderBuffer;
  float LiPosition[9*3];
  int nbLights;
  float invSS[2] = {static_cast<float>(1.0/ (2*_width)), static_cast<float>(1.0/(2*_height))};

  //SSAO
  GLuint SSAO;
  GLuint SSAOBLUR;
  RedBuffer ssaoBuffer;
  RedBuffer ssaoBufferBlur;
  float ssaoKernel[64*3];
  float ssaoNoise[16*3];
  //FloatTexture noiseTexture;
  GLuint noiseTexture;
  float ssaoRadius;
  float ssaoBias;
  bool computeSSAO;

  ShaderManager programs;

  // Camera
  std::unique_ptr<Camera> _camera;

  //Matrices
  glm::mat4 m_view;
  glm::mat4 m_projection;

  //Booleans
  bool m_animation = false;
  bool m_draw_aabb = false;

  //Booleans functions
  void setDrawAABB(bool d);
  void weightTresholdUp(bool up);
};

#endif // RendererGPUGPU_H
