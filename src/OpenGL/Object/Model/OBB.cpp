#include "OBB.h"
#include "../../opengl_stuff.h"

OBB::OBB() : Mesh (){}

void OBB::draw() const{
  glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
  box.draw();
  glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
}

OBB::OBB(glm::vec3 a,glm::vec3 b,glm::vec3 c,glm::vec3 d,glm::vec3 dir,float length) : Mesh(){
  box.computeCube(a,b,c,d,dir,length);
}
void OBB::computeOBB(glm::vec3 a,glm::vec3 b,glm::vec3 c,glm::vec3 d,glm::vec3 dir,float length){
  box.computeCube(a,b,c,d,dir,length);
}
