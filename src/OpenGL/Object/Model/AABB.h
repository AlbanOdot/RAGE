#ifndef AABB_H
#define AABB_H
#include "../Shapes/Cube.h"

class AABB
{
public:
  AABB();
  AABB(const glm::vec3& min, const glm::vec3& max);
  AABB(const std::vector<Mesh>& model);
  void computeAABB(const std::vector<Mesh>& model);
  void computeAABB(const glm::vec3& a,const glm::vec3& b, const glm::vec3& c, const glm::vec3& d, const glm::vec3& dir, const float length);
  void computeAABB(const glm::vec3& min, const glm::vec3& max);
  void draw() const;
  Mesh box() const { return m_box;}
  glm::vec3 center() const { return m_box.center();}
  glm::vec3 max() const  {return m_box.max();}
  glm::vec3 min() const { return m_box.min();}
private:
  Cube m_box;
};

#endif // AABB_H
