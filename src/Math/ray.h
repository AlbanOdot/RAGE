#ifndef RAY_H
#define RAY_H
#include <glm.hpp>

class Ray {
public:
  //RENDERER TracBall position               direction
  Ray():              m_o(glm::vec3(0,0,3)), m_d(glm::vec3(0,0,-1)), m_t(0){}
  Ray(glm::vec3 orig, glm::vec3 dir) : m_o(orig), m_d(dir), m_t(0){}
  glm::vec3 m_o;//origin
  glm::vec3 m_d;//direction
  glm::vec3 m_t;//current t
};

inline Ray transformRay(const Ray& r, const glm::mat4& t)
{
  glm::vec4 orig = glm::vec4(r.m_o,1);
  glm::vec4 dir = glm::vec4(r.m_o,0);
  return Ray(glm::vec3(t * orig), glm::vec3(t * dir) );
}

#endif // RAY_H
