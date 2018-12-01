#include "Bone.h"
#include <iostream>
#include "./src/Math/Algorithm.h"
#include <random>

unsigned int Bone::m_bone_count = 0;

Bone::Bone(glm::vec3 origin , glm::vec3 direction, float length , float radius )
  : Model(static_cast<unsigned char>('c')), m_id(m_bone_count++), m_root(true), m_origin(origin), m_direction(glm::normalize(direction)), m_length(length), m_radius(radius)
{
  direction = glm::normalize(direction);
  m_meshes.push_back(Cristal(origin,direction,length,radius));
  float sRadius = 0.25f * m_radius;
  m_meshes.push_back(Sphere(origin + (length + sRadius*0.5f) * direction, sRadius ));
  m_meshes.push_back(Sphere(origin - sRadius * direction,sRadius));//When Bone is not root we remove this

  //AABB computation
  //On swap les coordonnées pour avoir une base de R^3
  std::uniform_real_distribution<float> randomFloats(0.0001f,0.99f);
  std::default_random_engine  generator;
  float bias = randomFloats(generator);
  // For all bias  :  bias != (2 - bias) != bias^2 <=> 0<bias<1
  glm::vec3 base1(bias * direction.y, (2.f - bias) * direction.x, bias * bias *direction.z);
  bias = randomFloats(generator);
  glm::vec3 base2(bias * direction.y, (2.f - bias) * direction.z, bias * bias *direction.x);
  base1 = glm::normalize(base1);
  base2 = glm::normalize(base2);
  //Find orthonormal basis
  Math::Algorithm::GramSchmidt(direction,base1,base2);
  glm::vec3 a = radius * base1 + origin;
  glm::vec3 b = radius * base2 + origin;
  glm::vec3 c = -radius * base1 + origin;
  glm::vec3 d = -radius * base2 + origin;
  //Si c'est le root on inclut la première sphere
  if(m_root){
      a -= 2.f*sRadius * direction;
      b -= 2.f*sRadius * direction;
      c -= 2.f*sRadius * direction;
      d -= 2.f*sRadius * direction;
    }

  //+radius pour les deux spheres
  m_aabb.computeAABB(a,b,c,d,direction,length + radius);
  //m_aabb.computeAABB(m_meshes);
}

void Bone::draw() const{

  //Draw self
  for(const auto& mesh : m_meshes ){
      mesh.draw();
    }

  //Draw children depth first
  for(const auto& child : m_children){
      child.draw();
    }
  if(m_draw_aabb){
      m_aabb.draw();
    }
}

/* Hierarchy functions */
Bone Bone::addChild(glm::vec3 direction, float length, float radius){
  Bone child(m_origin + m_length * m_direction, direction, length, radius);
  child.setRoot(false);
  m_children.push_back(child);
  return child;
}

void Bone::addChild(Bone& child){
  child.setRoot(false);
  m_children.push_back(child);
}

Bone Bone::addChild(deque<int> path,glm::vec3 direction, float length, float radius){
  if(path.size() == 0)
    return addChild(direction, length, radius);
  int son = path[0];
  if(son >= m_children.size())
    return Bone();
  path.pop_front();
  return m_children[son].addChild(path, direction,length,radius);
}

int Bone::clickOnSkeletton(Ray& r)const{
  if(Math::RayCast::vsAABB(r,m_aabb))
    return (int)m_id;
  int ID = -1;
  for(const auto& child : m_children){
      if( (ID = child.clickOnSkeletton(r)) != -1)
        return ID;
    }
  return -1;
}

void Bone::setAABB(bool d){
  cout << "Bone "<<m_id<< " has been set"<<endl;
  m_draw_aabb = d;
  for(auto& child : m_children){
      child.setAABB(d);
    }
}
void Bone::addParent(const Bone& parent){
  m_parents.push_back(parent);
}

void Bone::setRoot(bool root){
  m_root = root;
  if(m_meshes.size() == 3){
      m_meshes.pop_back();
    }
}

/* Hierarchy  action functions */
void Bone::rotate(float theta, glm::vec3 u){
  m_model = glm::rotate(m_model, theta, u);
  float ct = glm::cos(theta);
  float st = glm::sin(theta);
  float uct = 1.f - ct;
  glm::mat4 R;
  R[0][0] = ct + u.x*u.x *uct; R[0][1] = u.x*u.y*uct - u.z*st; R[0][2] = u.x*u.z*uct + u.y*st;
  R[1][0] = R[0][1]; R[1][1] = ct + u.y*u.y*uct;R[1][2] = u.y*u.z*uct-u.x*st;
  R[2][0] = R[0][2]; R[2][1] = R[1][2]; R[2][2] = ct + u.z*u.z*uct;
  R[3][0] = m_origin.x;R[3][1] = m_origin.y;R[3][2] = m_origin.z;

  m_model *= R;
  for(auto& child : m_children){
      child.rotate(R);
    }

}
//void rotate(Quaternion q);
//void stretch(glm::vec3 direction, float length);

/* Action functions */
void Bone::rotate(const glm::mat4& R){
  m_model *= R;
  for(auto& child : m_children){
      child.rotate(R);
    }
}
//void rotateLocal(float theta);
//void rotateLocal(Quaternion q);
