#include "Bone.h"
#include <iostream>
#define GLM_ENABLE_EXPERIMENTAL
#include <glm/gtx/transform.hpp>
#include <glm/gtx/vector_angle.hpp>
#include "./src/Math/Algorithm.h"

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
  glm::vec3 up(0,1,0);
  glm::vec3 base1(glm::rotateX(direction,(float)M_PI * 0.25f));
  glm::vec3 base2(glm::rotateY(direction,(float)M_PI * 0.75f));
  //Find orthonormal basis
  GramSchmidt(direction,base1,base2);
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
  if(m_draw_aabb)
    m_aabb.draw();
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
  //TODO FINIR LE 4X4 POUR LA ROTATION

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
}
//void rotateLocal(float theta);
//void rotateLocal(Quaternion q);
