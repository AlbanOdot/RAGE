#include "Algorithm.h"

/*
 * Trouve une base orthonomée à partir du vecteur v1
 *
 * Modifie les vecteurs u1 et u2
 */
void Math::Algorithm::GramSchmidt(const glm::vec3& u1, glm::vec3& u2, glm::vec3& u3){
  u2 = u2 - projection(u1,u2);
  u2 = glm::normalize(u2);
  u3 = u3 - projection(u1,u3) - projection(u2,u3);
  u3 = glm::normalize(u3);
}

/*
 * project v onto u
 * projection(v,u) = v * (dot(u,v) / dot(v,v))
 *
 */
glm::vec3 Math::Algorithm::projection(const glm::vec3& v, const glm::vec3& u){
  return v * (glm::dot(u,v) / glm::dot(v,v));
}
