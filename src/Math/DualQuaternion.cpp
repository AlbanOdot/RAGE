#include "DualQuaternion.h"
#include <iostream>
using namespace Math;

DualQuaternion::DualQuaternion()
{
    DualQuaternion res = dual_quat_from(Quaternion(), glm::vec3(0.f, 0.f, 0.f));
    *this = res;
}
DualQuaternion::DualQuaternion(const Quaternion& q0, const Quaternion& qe)
{
    m_quat_0 = q0;
    m_quat_e = qe;
}
DualQuaternion::DualQuaternion(const Quaternion& q, const glm::vec3& t)
{
    DualQuaternion res = dual_quat_from(q, t);
    *this = res;
}
DualQuaternion::DualQuaternion(const glm::mat4& t)
{
    Quaternion q(t);
    glm::vec3 translation(t[0][3], t[1][3], t[2][3]);
    DualQuaternion res = dual_quat_from(q, translation);
    *this = res;
}
void DualQuaternion::normalize()
{
    float norm = m_quat_0.norm();
    m_quat_0 = m_quat_0 / norm;
    m_quat_e = m_quat_e / norm;
}

glm::vec3 DualQuaternion::transform(const glm::vec3& p ) const
{
    float norm = m_quat_0.norm();
    Quaternion qblend_0 = m_quat_0 / norm;
    Quaternion qblend_e = m_quat_e / norm;
    glm::vec3 v0 = qblend_0.get_vec_part();
    glm::vec3 ve = qblend_e.get_vec_part();
    glm::vec3 trans = (ve*qblend_0.w() - v0*qblend_e.w() + glm::cross(v0,ve)) * 2.f;

    // Rotate
    return qblend_0.rotate(p) + trans;
}

glm::vec3 DualQuaternion::rotate(const glm::vec3& v) const
{
    Quaternion tmp = m_quat_0;
    tmp.normalize();
    return tmp.rotate(v);
}

DualQuaternion DualQuaternion::dual_quat_from(const Quaternion& q, const glm::vec3& t) const
{
    float w = -0.5f*( t.x * q.i() + t.y * q.j() + t.z * q.k());
    float i =  0.5f*( t.x * q.w() + t.y * q.k() - t.z * q.j());
    float j =  0.5f*(-t.x * q.k() + t.y * q.w() + t.z * q.i());
    float k =  0.5f*( t.x * q.j() - t.y * q.i() + t.z * q.w());

    return DualQuaternion(q, Quaternion(w, i, j, k));
}

void DualQuaternion::translate(const glm::vec3& t){
  float w = -0.5f*( t.x * m_quat_0.i() + t.y * m_quat_0.j() + t.z * m_quat_0.k());
  float i =  0.5f*( t.x * m_quat_0.w() + t.y * m_quat_0.k() - t.z * m_quat_0.j());
  float j =  0.5f*(-t.x * m_quat_0.k() + t.y * m_quat_0.w() + t.z * m_quat_0.i());
  float k =  0.5f*( t.x * m_quat_0.j() - t.y * m_quat_0.i() + t.z * m_quat_0.w());
  m_quat_e = Quaternion(w, i, j, k);
}

glm::mat4 DualQuaternion::to_transformation()
{
    glm::vec3 t;
    float norm = m_quat_0.norm();

    glm::mat3 m = (m_quat_0 / norm).to_matrix3();

    t.x = 2.f*(-m_quat_e.w()*m_quat_0.i() + m_quat_e.i()*m_quat_0.w() - m_quat_e.j()*m_quat_0.k() + m_quat_e.k()*m_quat_0.j()) / norm;
    t.y = 2.f*(-m_quat_e.w()*m_quat_0.j() + m_quat_e.i()*m_quat_0.k() + m_quat_e.j()*m_quat_0.w() - m_quat_e.k()*m_quat_0.i()) / norm;
    t.z = 2.f*(-m_quat_e.w()*m_quat_0.k() - m_quat_e.i()*m_quat_0.j() + m_quat_e.j()*m_quat_0.i() + m_quat_e.k()*m_quat_0.w()) / norm;


    return glm::translate(glm::mat4(m),-t);
}

DualQuaternion DualQuaternion::operator+(const DualQuaternion& dq) const
{
    return DualQuaternion(m_quat_0 + dq.m_quat_0, m_quat_e + dq.m_quat_e);
}

DualQuaternion DualQuaternion::operator*(float scalar) const
{
    return DualQuaternion(m_quat_0 * scalar, m_quat_e * scalar);
}

DualQuaternion DualQuaternion::operator*(const DualQuaternion& q) const
{
    return DualQuaternion(m_quat_0 * q.m_quat_0, m_quat_e * q.m_quat_e);
}

DualQuaternion DualQuaternion::identity()
{
    return DualQuaternion(Quaternion(1.f, 0.f, 0.f, 0.f),glm::vec3(0.f, 0.f, 0.f) );
}
