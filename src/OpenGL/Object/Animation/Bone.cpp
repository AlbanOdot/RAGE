#include "Bone.h"
#include <iostream>
unsigned int Bone::m_bone_count = 0;

Bone::Bone(glm::vec3 origin , glm::vec3 direction, float length , float radius )
  : Model(static_cast<unsigned char>('c')), m_id(m_bone_count++), m_root(true), m_origin(origin), m_direction(direction), m_length(length), m_radius(radius)
{
  m_meshes.push_back(Cristal(m_origin,m_direction,m_length-m_radius/2,m_radius));
  float sRadius = 0.25f * m_radius;
  m_meshes.push_back(Sphere(origin + (length - sRadius) * direction, sRadius ));
  m_meshes.push_back(Sphere(origin - sRadius * direction,sRadius));//When Bone is not root we remove this
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
}

/* Hierarchy functions */
Bone Bone::addChild(glm::vec3 direction, float length, float radius){
  Bone child(m_origin + m_length * m_direction, direction, length, radius);
  child.setRoot(false);
  m_children.push_back(child);
  cout << "Bone "<< m_id<<" now has "<< m_children.size() << " child(ren)"<<endl;
  return child;
}

void Bone::addChild(Bone& child){
  child.setRoot(false);
  m_children.push_back(child);
}

Bone Bone::addParent(glm::vec3 direction, float length, float radius){
  m_root = false;
  Bone parent(m_origin - m_length*m_direction, direction, length, radius);
  m_parents.push_back(parent);
  return parent;
}

void Bone::addParent(const Bone& parent){
  m_root = false;
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
