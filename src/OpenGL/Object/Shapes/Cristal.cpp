#include "Cristal.h"
#include "./src/Math/Algorithm.h"

Cristal::Cristal(glm::vec3 origin , glm::vec3 direction, float length, float radius)
  : Shape(CRISTAL), m_origin(origin), m_direction(direction), m_length(length), m_radius(radius)
{
  //Generate 4 points
  glm::vec3 base1;
  glm::vec3 base2;
  Math::Algorithm::generateOrthonormalBasisFromDirection(direction,base1,base2);
  glm::vec3 b0 = origin + 0.5f*radius*base1 + 0.3f * direction;
  glm::vec3 b1 = origin + -0.5f*radius*(base1+base2) + 0.3f * direction;
  glm::vec3 b2 = origin + 0.5f * radius*base2 + 0.3f * direction;
  glm::vec3 top = origin + length * direction;
  glm::vec3 bottom = origin;

  Point3(b0.x, b0.y, b0.z);
  Point3(b1.x, b1.y, b1.z);
  Point3(b2.x, b2.y, b2.z);
  Point3(top.x, top.y, top.z);
  Point3(bottom.x, bottom.y, bottom.z);

  Colors(0.,0.,0.);
  Colors(0.,0.,0.);
  Colors(0.,0.,0.);
  Colors(0.,0.,0.);
  Colors(0.,0.,0.);

  Point2(0.,0.);
  Point2(0.,0.);
  Point2(0.,0.);
  Point2(0.,0.);
  Point2(0.,0.);

  glm::vec3 G = 0.20f * (b0+b1+b2+top+bottom);
  top = glm::normalize(top - G);b0 = glm::normalize(b0 - G);b1 = glm::normalize(b1 - G); b2 = glm::normalize(b2-G); bottom = glm::normalize(bottom - G);
  Normal(b0.x, b0.y, b0.z);
  Normal(b1.x, b1.y, b1.z);
  Normal(b2.x, b2.y, b2.z);
  Normal(top.x, top.y, top.z);
  Normal(bottom.x, bottom.y, bottom.z);

  //TOP hat
  Triangle(0,2,3);
  Triangle(2,1,3);
  Triangle(1,0,3);
  //Bottom hat
  Triangle(2,0,4);
  Triangle(1,2,4);
  Triangle(0,1,4);

  setupMesh();
}
