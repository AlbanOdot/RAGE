#ifndef AABB_H
#define AABB_H
#include "mesh.h"
#include "../Shapes/Cube.h"

class AABB : public Mesh
{
public:
  virtual ~AABB(){}
  AABB();
  AABB(std::vector<Mesh> model);
  void computeAABB(std::vector<Mesh> model);
  //
  void computeAABB(glm::vec3 a,glm::vec3 b,glm::vec3 c,glm::vec3 d,glm::vec3 dir,float length);
  virtual void draw() const;
private:
  Cube box;
};

#endif // AABB_H
