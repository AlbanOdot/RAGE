#ifndef DUALQUATERNION_H
#define DUALQUATERNION_H
class DualQuaternion
{
public:
  Quaternion m_real;
  Quaternion m_dual;
  DualQuaternion(){
    m_real = new Quaternion(0,0,0,1);
    m_dual = new Quaternion(0,0,0,0);
  }
  DualQuaternion( Quaternion r, Quaternion d ){
    m_real = Quaternion.Normalize( r );
    m_dual = d;
  }
  DualQuaternion( Quaternion r, Vector3 t ){
    m_real = Quaternion.Normalize( r );
    m_dual = ( new Quaternion( t, 0 ) * m_real ) * 0.5f;
  }
  float Dot( DualQuaternion a,DualQuaternion b ){
    return Quaternion.Dot( a.m_real, b.m_real );
  }
  DualQuaternion operator* (DualQuaternion q, float scale){
    DualQuaternion ret = q;
    ret.m_real *= scale;
    ret.m_dual *= scale;
    return ret;
  }
  DualQuaternion Normalize( DualQuaternion q){
    float mag = Quaternion.Dot( q.m_real, q.m_real );
    DualQuaternion ret = q;
    ret.m_real *= 1.0f / mag;
    ret.m_dual *= 1.0f / mag;
    return ret;
  }
  DualQuaternion operator + (DualQuaternion lhs, DualQuaternion rhs){
    return new DualQuaternion(lhs.m_real + rhs.m_real,lhs.m_dual + rhs.m_dual);
  }
  // Multiplication order - left to right
  DualQuaternion operator * (DualQuaternion lhs, DualQuaternion rhs){
    return new DualQuaternion(rhs.m_real*lhs.m_real,rhs.m_dual*lhs.m_real + rhs.m_real*lhs.m_dual);
  }
  DualQuaternion Conjugate( DualQuaternion q){
    return new DualQuaternion( Quaternion.Conjugate(q.m_real ), Quaternion.Conjugate( q.m_dual ) );
  }
  Quaternion GetRotation( DualQuaternion q ){
    return q.m_real;
  }
  glm::vec3 GetTranslation( DualQuaternion q ){
    Quaternion t = ( q.m_dual * 2.0f ) * Quaternion.Conjugate(q.m_real );
    return new glm::vec3( t.X, t.Y, t.Z );
  }
  glm::mat4 DualQuaternionToMatrix(DualQuaternion q ){
    q = DualQuaternion.Normalize( q );
    glm::mat4 M;
    float w = q.m_real.W;
    float x = q.m_real.X;
    float y = q.m_real.Y;
    float z = q.m_real.Z;
    // Extract rotational information
    M.M11 = w*w + x*x - y*y - z*z;
    M.M12 = 2*x*y + 2*w*z;
    M.M13 = 2*x*z - 2*w*y;

    M.M21 = 2*x*y - 2*w*z;
    M.M22 = w*w + y*y - x*x - z*z;
    M.M23 = 2*y*z + 2*w*x;
    M.M31 = 2*x*z + 2*w*y;
    M.M32 = 2*y*z - 2*w*x;
    M.M33 = w*w + z*z - x*x - y*y;
    // Extract translation information
    Quaternion t = (q.m_dual * 2.0f) * Quaternion.Conjugate(
          q.m_real);
    M.M41 = t.X;
    M.M42 = t.Y;
    M.M43 = t.Z;
    return M;
  }
};
#endif // DUALQUATERNION_H
