#ifndef BONE_H
#define BONE_H

#include "./src/OpenGL/Object/model.h"

class Bone : public Model
{
public:
  Bone(glm::vec3 origin = glm::vec3(-1.0,0.0,0.0), glm::vec3 direction = glm::vec3(1.0,0.0,0.0), float length = 2.0, float radius = 0.3);

protected:
  glm::vec3 m_origin;
  glm::vec3 m_direction;
  float m_length;
  float m_radius;
};

#endif // BONE_H
