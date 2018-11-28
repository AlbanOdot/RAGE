#include "Tetrahedron.h"

Tetrahedron::Tetrahedron(glm::vec3 origin, glm::vec3 direction, float length, float radius)
  : Shape(TETRAHEDRON), m_origin(origin), m_direction(direction), m_length(length), m_radius(radius)
{
  //Generate 4 points
  glm::vec3 b1 = origin + glm::vec3(0.0,radius/2,0.0);
  glm::vec3 b2 = origin + glm::vec3(0.0,-radius/2,0.0);
  glm::vec3 b3 = origin + glm::vec3(0.0,0.0,radius/2);
  glm::vec3 top = origin + length * direction;
  Point3(b1.x, b1.y, b1.z);
  Point3(b2.x, b2.y, b2.z);
  Point3(b3.x, b3.y, b3.z);
  Point3(top.x, top.y, top.z);
  Colors(0.,0.,0.);
  Colors(0.,0.,0.);
  Colors(0.,0.,0.);
  Colors(0.,0.,0.);
  Point2(0.,0.);
  Point2(0.,0.);
  Point2(0.,0.);
  Point2(0.,0.);
  glm::vec3 G = 0.25f * (b1+b2+b3+top);
  top = glm::normalize(top - G);b1 = glm::normalize(b1 - G);b2 = glm::normalize(b2 - G); b3 = glm::normalize(b3-G);
  Normal(b1.x, b1.y, b1.z);
  Normal(b2.x, b2.y, b2.z);
  Normal(b3.x, b3.y, b3.z);
  Normal(top.x, top.y, top.z);
  Triangle(0,1,2);
  Triangle(0,2,3);
  Triangle(2,1,3);
  Triangle(1,0,3);
  setupMesh();
}
