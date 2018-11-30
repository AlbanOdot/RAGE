#include "Tetrahedron.h"

Tetrahedron::Tetrahedron(glm::vec3 origin, glm::vec3 direction, float length, float radius)
  : Shape(TETRAHEDRON), m_origin(origin), m_direction(direction), m_length(length), m_radius(radius)
{
  //Generate 4 points
  glm::vec3 b0 = origin + glm::vec3(0.0,radius,0.0);
  glm::vec3 b1 = origin + glm::vec3(0.0,-radius,0.0);
  glm::vec3 b2 = origin + glm::vec3(0.0,0.0,radius);
  glm::vec3 top = origin + length * direction;
  Point3(b0.x, b0.y, b0.z);
  Point3(b1.x, b1.y, b1.z);
  Point3(b2.x, b2.y, b2.z);
  Point3(top.x, top.y, top.z);
  Colors(0.,0.,0.);
  Colors(0.,0.,0.);
  Colors(0.,0.,0.);
  Colors(0.,0.,0.);
  Point2(0.,0.);
  Point2(0.,0.);
  Point2(0.,0.);
  Point2(0.,0.);
  glm::vec3 G = 0.25f * (b0+b1+b2+top);
  top = glm::normalize(top - G);b0 = glm::normalize(b0 - G);b1 = glm::normalize(b1 - G); b2 = glm::normalize(b2-G);
  Normal(b0.x, b0.y, b0.z);
  Normal(b1.x, b1.y, b1.z);
  Normal(b2.x, b2.y, b2.z);
  Normal(top.x, top.y, top.z);
  Triangle(0,1,2);
  Triangle(0,2,3);
  Triangle(2,1,3);
  Triangle(1,0,3);
  setupMesh();
}
