#ifndef ALGORITHM_H
#define ALGORITHM_H
#include "glm.hpp"
#define GLM_ENABLE_EXPERIMENTAL
#include <glm/gtx/transform.hpp>
#include <glm/gtx/vector_angle.hpp>

#include <vector>

namespace  Math{

  namespace Algorithm{
#define SQRT2 1.414213562373095048801688724209698f
#define SQRT1_2  0.7071067811865475255008f
#define EPSILON 0.000000001f
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

    /*
     *
     *
     *
     */
    inline void find4MaxValues(const std::vector<float>& findIn, glm::vec4& foundOut, glm::vec4& foundOutIdx);
    /*
     *
     *
     *
     */
    inline void generateOrthonormalBasisFromDirection(glm::vec3& direction, glm::vec3& x, glm::vec3& y);
  }
}

#include "Algorithm.inl"

#endif //ALGORITHM_H
