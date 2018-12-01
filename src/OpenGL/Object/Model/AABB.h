#ifndef AABB_H
#define AABB_H
#include "../Shapes/Cube.h"

class AABB
{
public:
  AABB();
  AABB(std::vector<Mesh> model);
  void computeAABB(std::vector<Mesh> model);
  //
  void computeAABB(glm::vec3 a,glm::vec3 b,glm::vec3 c,glm::vec3 d,glm::vec3 dir,float length);
  void draw() const;
  Mesh box() const { return m_box;}
private:
  Cube m_box;
};

#endif // AABB_H
