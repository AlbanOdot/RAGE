#ifndef QUATERNION_H
#define QUATERNION_H
#include "glm.hpp"
#define GLM_ENABLE_EXPERIMENTAL
#include <glm/gtx/transform.hpp>
#include <glm/gtx/vector_angle.hpp>

namespace Math{
  class Quaternion
  {
  public:
    Quaternion();
    Quaternion(const Quaternion& q);
    Quaternion(float w, float i, float j, float k);
    Quaternion(float w, const glm::vec3& v);
    Quaternion(const glm::mat4& t);
    Quaternion(const glm::vec3& axis, float angle);
    Quaternion(const glm::vec4& q);


    Quaternion conjugate() const;
    glm::vec3 rotate(const glm::vec3& p) const;
    glm::mat3 to_matrix3();
    glm::vec3 get_vec_part() const;
    float norm() const;
    float normalize();
    float dot(const Quaternion& q);
    float w() const { return m_coef.x; }
    float i() const { return m_coef.y; }
    float j() const { return m_coef.z; }
    float k() const { return m_coef.w; }

    Quaternion operator/ (float scalar) const;
    Quaternion operator/= (float scalar);
    Quaternion operator* (const Quaternion& q) const;
    Quaternion operator* (float scalar) const;
    Quaternion operator+ (const Quaternion& q) const;
    /// Get vector part
    operator glm::vec3 () const;
    /// Get scalar part
    operator float () const;

    glm::vec4 m_coef;
  };
}
#endif // QUATERNION_H
