#ifndef DUALQUATERNION_H
#define DUALQUATERNION_H
#include "Quaternion.h"

namespace Math{
  class DualQuaternion
  {
  public:

    DualQuaternion();
    DualQuaternion(const Quaternion& q0, const Quaternion& qe);
    DualQuaternion(const Quaternion& q, const glm::vec3& t);
    DualQuaternion(const glm::mat4& t);

    void normalize();
    glm::vec3 transform(const glm::vec3& p ) const;
    glm::vec3 rotate(const glm::vec3& v) const;
    DualQuaternion dual_quat_from(const Quaternion& q, const glm::vec3& t) const;
    void translate(const glm::vec3& t);
    glm::mat4 to_transformation();

    DualQuaternion operator+(const DualQuaternion& dq) const;
    DualQuaternion operator*(float scalar) const;
    DualQuaternion operator*(const DualQuaternion& q) const;

    static DualQuaternion identity();
    Quaternion get_dual_part() const { return m_quat_e; }
    Quaternion get_non_dual_part() const { return m_quat_0; }
    Quaternion translation() const { return m_quat_e;}
    Quaternion rotation() const { return m_quat_0; }
    void set_rotation( const Quaternion& q ){ m_quat_0 = q; }
    Quaternion q0() const { return m_quat_0;}
    Quaternion qe() const { return m_quat_e;}
  private:
    Quaternion m_quat_0;
    Quaternion m_quat_e;
  };
}
#endif // DUALQUATERNION_H
