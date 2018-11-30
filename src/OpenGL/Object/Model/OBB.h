#ifndef OBB_H
#define OBB_H
#include "mesh.h"
#include "../Shapes/Cube.h"

class OBB : Mesh
{
public:
  virtual ~OBB(){}
  OBB();
  OBB(glm::vec3 a,glm::vec3 b,glm::vec3 c,glm::vec3 d,glm::vec3 dir,float length);
  //TODO ACP
  //OBB(std::vector<Mesh> model);
  //void computeOBB(std::vector<Mesh> model);
  //Improve bone precision
  void computeOBB(glm::vec3 a,glm::vec3 b,glm::vec3 c,glm::vec3 d,glm::vec3 dir,float length);
  virtual void draw() const;
private:
  Cube box;
};
#endif // OBB_H
