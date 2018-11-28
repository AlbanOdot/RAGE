#ifndef SPHERE_H
#define SPHERE_H
#include "./Shape.h"
#include <glm/glm.hpp>

class Sphere : public Shape
{
public:
  Sphere(glm::vec3 center, float radius);

private:
  glm::vec3 m_center;
  float m_radius;
};

#endif // SPHERE_H
