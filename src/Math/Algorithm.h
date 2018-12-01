#ifndef ALGORITHM_H
#define ALGORITHM_H
#include "glm.hpp"
#define GLM_ENABLE_EXPERIMENTAL
#include <glm/gtx/transform.hpp>
#include <glm/gtx/vector_angle.hpp>

namespace  Math{

  namespace Algorithm{
#define SQRT2 1.414213562373095048801688724209698
#define SQRT1_2  0.7071067811865475255008
    /*
 * Trouve une base orthonomée à partir du vecteur v1
 *
 * Modifie les vecteurs u1 et u2
 */
    inline void GramSchmidt(const glm::vec3& v, glm::vec3& u1, glm::vec3& u2);

    /*
 *
 * projection(v,u) = v * (dot(u,v) / dot(v,v))
 *
 */
    inline glm::vec3 projection(const glm::vec3& v, const glm::vec3& u);
  };
};

#include "Algorithm.inl"

#endif //ALGORITHM_H
