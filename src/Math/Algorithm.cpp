#include "Algorithm.h"

/*
 * Trouve une base orthonomée à partir du vecteur v1
 *
 * Modifie les vecteurs u1 et u2
 */
void GramSchmidt(const glm::vec3& v, glm::vec3& u1, glm::vec3& u2){
  u1 = u1 - projection(v,u1);
  u1 = glm::normalize(u1);
  u2 = u2 - projection(v,u1) - projection(v,u2);
  u2 = glm::normalize(u2);
}

/*
 *
 * projection(v,u) = v * (dot(u,v) / dot(v,v))
 *
 */
glm::vec3 projection(const glm::vec3& v, const glm::vec3& u){
  return v * (glm::dot(u,v) / glm::dot(v,v));
}
