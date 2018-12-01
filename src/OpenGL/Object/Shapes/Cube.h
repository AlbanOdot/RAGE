#ifndef CUBE_H
#define CUBE_H
#include "glm.hpp"
#include "Shape.h"

class Cube : public Shape
{
public:
  virtual ~Cube(){}
  Cube();
  Cube(glm::vec3 min,glm::vec3 max);
  Cube(glm::vec3 a,glm::vec3 b,glm::vec3 c,glm::vec3 d,glm::vec3 dir,float length);
  void computeCube(glm::vec3 min,glm::vec3 max);
  void computeCube(glm::vec3 a,glm::vec3 b,glm::vec3 c,glm::vec3 d,glm::vec3 dir,float length);
  virtual void draw() const;
  glm::vec3 max() const { return m_max;}
  glm::vec3 min() const { return m_min;}
  glm::vec3 center() const { return 0.5f * (m_max + m_min);}
private:
  glm::vec3 m_max;
  glm::vec3 m_min;
  glm::vec3 m_topLeftFront;
  glm::vec3 m_topRightFront;
  glm::vec3 m_topLeftBack;
  glm::vec3 m_topRightBack;
  glm::vec3 m_botLeftFront;
  glm::vec3 m_botRightFront;
  glm::vec3 m_botLeftBack;
  glm::vec3 m_botRightBack;
};
#endif // CUBE_H
