#ifndef CRISTAL_H
#define CRISTAL_H
#include "./Shape.h"
#include <glm/glm.hpp>

class Cristal : public Shape
{
public:
  Cristal(glm::vec3 origin = glm::vec3(-1.0,0.0,0.0), glm::vec3 direction = glm::vec3(1.0,0.0,0.0), float length = 2.0, float radius = 0.5);
private:
  glm::vec3 m_origin;
  glm::vec3 m_direction;
  float m_length;
  float m_radius;
};

#endif // CRISTAL_H
