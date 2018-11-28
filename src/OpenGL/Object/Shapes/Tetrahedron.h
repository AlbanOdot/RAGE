#ifndef TETRAHEDRON_H
#define TETRAHEDRON_H
#include "./Shape.h"
#include <glm/glm.hpp>

class Tetrahedron : public Shape
{
public:
  Tetrahedron(glm::vec3 origin = glm::vec3(-1.0,0.0,0.0), glm::vec3 direction = glm::vec3(1.0,0.0,0.0), float length = 2.0, float radius = 0.3);
private:
  glm::vec3 m_origin;
  glm::vec3 m_direction;
  float m_length;
  float m_radius;
};

#endif // TETRAHEDRON_H
