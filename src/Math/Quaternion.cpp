#include "Quaternion.h"

using namespace Math;

Quaternion::Quaternion()
{
  m_coef.x = 1.f;
  m_coef.y = 0.f; m_coef.z = 0.f; m_coef.w = 0.f;
}

Quaternion::Quaternion(const Quaternion& q){
  m_coef.x = q.w();
  m_coef.y = q.i(); m_coef.z = q.j(); m_coef.w = q.k();
}

Quaternion::Quaternion(const glm::vec4& q){
  m_coef = q;
}


Quaternion::Quaternion(float w, float i, float j, float k){
  m_coef.x = w;
  m_coef.y = i; m_coef.z = j; m_coef.w = k;
}

Quaternion::Quaternion(float w, const glm::vec3& v){
  m_coef.x = w;
  m_coef.y = v.x; m_coef.z = v.y; m_coef.w = v.z;
}

Quaternion::Quaternion(const glm::mat4& t)
{
  // Compute trace of matrix 't'
  float T = 1.f + t[0][0] + t[1][1] + t[2][2];

  float S, X, Y, Z, W;

  if ( T > 0.00000001f ) // to avoid large distortions!
    {
      S = sqrt(T) * 2.f;
      X = ( t[1][2] - t[2][1] ) / S;
      Y = ( t[2][0] - t[0][2] ) / S;
      Z = ( t[0][1] - t[1][0] ) / S;
      W = 0.25f * S;
    }
  else
    {
      if ( t[0][0] > t[1][1] && t[0][0] > t[2][2] )
        {
          // Column 0 :
          S  = sqrt( 1.0f + t[0][0] - t[1][1] - t[2][2] ) * 2.f;
          X = 0.25f * S;
          Y = (t[0][1] + t[1][0] ) / S;
          Z = (t[2][0] + t[0][2] ) / S;
          W = (t[1][2] - t[2][1] ) / S;
        }
      else if ( t[1][1] > t[2][2] )
        {
          // Column 1 :
          S  = sqrt( 1.0f + t[1][1] - t[0][0] - t[2][2] ) * 2.f;
          X = (t[0][1] + t[1][0] ) / S;
          Y = 0.25f * S;
          Z = (t[1][2] + t[2][1] ) / S;
          W = (t[2][0] - t[0][2] ) / S;
        }
      else
        {   // Column 2 :
          S  = sqrt( 1.0f + t[2][2] - t[0][0] - t[1][1] ) * 2.f;
          X = (t[2][0] + t[0][2] ) / S;
          Y = (t[1][2] + t[2][1] ) / S;
          Z = 0.25f * S;
          W = (t[0][1] - t[1][0] ) / S;
        }
    }
  m_coef = glm::vec4(W,-X,-Y,-Z);
}

Quaternion::Quaternion(const glm::vec3& axis, float angle)
{
  glm::vec3 vec_axis = glm::normalize(axis);
  float sin_a = glm::sin( angle * 0.5f );
  float cos_a = glm::cos( angle * 0.5f );
  m_coef.x    = cos_a;
  m_coef.y    = vec_axis.x * sin_a;
  m_coef.z    = vec_axis.y * sin_a;
  m_coef.w    = vec_axis.z * sin_a;
  glm::normalize(m_coef);
}

Quaternion Quaternion::conjugate() const
{
  return Quaternion( m_coef.x, -m_coef.y,-m_coef.z, -m_coef.w);
}

glm::vec3 Quaternion::rotate(const glm::vec3& v) const
{
  glm::vec3 q_vec = get_vec_part();
  return v + glm::cross((q_vec*2.f),( glm::cross(q_vec,v) + v*m_coef.x ));
}

glm::mat3 Quaternion::to_matrix3()
{
  float W = m_coef.x, X = -m_coef.y, Y = -m_coef.z, Z = -m_coef.w;
  float xx = X * X, xy = X * Y, xz = X * Z, xw = X * W;
  float yy = Y * Y, yz = Y * Z, yw = Y * W, zz = Z * Z;
  float zw = Z * W;
  glm::mat3 mat = glm::mat3(
        1.f - 2.f * (yy + zz),      2.f * (xy + zw),       2.f * (xz - yw),
        2.f * (xy - zw),1.f - 2.f * (xx + zz),       2.f * (yz + xw),
        2.f * (xz + yw),      2.f * (yz - xw), 1.f - 2.f * (xx + yy)
        );

  return mat;
}

glm::vec3 Quaternion::get_vec_part() const
{
  return glm::vec3(m_coef.y, m_coef.z, m_coef.w);
}

float Quaternion::norm() const
{
  return glm::length(m_coef);
}

float Quaternion::normalize()
{
  float n = glm::length(m_coef);
  m_coef /= n;
  return n;
}

float Quaternion::dot(const Quaternion& q){

  return glm::dot(m_coef,q.m_coef);
}

Quaternion Quaternion::operator/ (float scalar) const
{
  Quaternion q = *this;
  q.m_coef.x /= scalar;  q.m_coef.y /= scalar;  q.m_coef.z /= scalar;  q.m_coef.w /= scalar;
  return q;
}

Quaternion Quaternion::operator/= (float scalar){
  return *this/scalar;
}

Quaternion Quaternion::operator* (const Quaternion& q) const
{
  return Quaternion(
        m_coef.x*q.m_coef.x - m_coef.y*q.m_coef.y - m_coef.z*q.m_coef.z - m_coef.w*q.m_coef.w,
        m_coef.x*q.m_coef.y + m_coef.y*q.m_coef.x + m_coef.z*q.m_coef.w - m_coef.w*q.m_coef.z,
        m_coef.x*q.m_coef.z + m_coef.z*q.m_coef.x + m_coef.w*q.m_coef.y - m_coef.y*q.m_coef.w,
        m_coef.x*q.m_coef.w + m_coef.w*q.m_coef.x + m_coef.y*q.m_coef.z - m_coef.z*q.m_coef.y);
}

Quaternion Quaternion::operator* (float scalar) const
{
  return Quaternion(scalar*m_coef);
}

Quaternion Quaternion::operator+ (const Quaternion& q) const
{
  return Quaternion(m_coef + q.m_coef);
}

/// Get vector part
Quaternion::operator glm::vec3 () const{
  return glm::vec3(m_coef.y, m_coef.z, m_coef.w);
}

/// Get scalar part
Quaternion::operator float () const{
  return m_coef.x;
}
