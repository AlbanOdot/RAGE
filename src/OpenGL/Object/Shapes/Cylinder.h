#ifndef CYLINDER_H
#define CYLINDER_H
#include "Shape.h"

class Cylinder : public Shape
{
public:
  Cylinder(glm::vec3 origin = glm::vec3(-1.0,0.0,0.0), glm::vec3 direction = glm::vec3(1.0,0.0,0.0), float length = 2.0, float radius = 0.5);
private:
  glm::vec3 m_origin;
  glm::vec3 m_direction;
  float m_length;
  float m_radius;
};

#endif // CYLINDER_H
