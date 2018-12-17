#include "Bone.h"
#include <iostream>
#include "./src/Math/Algorithm.h"
#include "./src/OpenGL/Object/Shapes/shapes.h"
#include <random>
#include <cmath>

unsigned int Bone::m_bone_count = 0;

Bone::Bone(glm::vec3 origin , glm::vec3 direction, float length , float radius, bool root )
  : BasicModel(), m_id(m_bone_count++), m_root(root), m_origin(origin), m_direction(glm::normalize(direction)), m_length(length), m_radius(radius)
{
  computeBone(origin,direction,length,radius,root);
}


void Bone::computeBone(glm::vec3 origin , glm::vec3 direction, float length , float radius, bool root ){
  m_meshes.clear();
  direction = glm::normalize(direction);
  m_meshes.push_back(Cristal(origin,direction,length,radius));
  float sRadius = 0.25f * m_radius;
  m_meshes.push_back(Sphere(origin + (length + sRadius*0.5f) * direction, sRadius ));
  if(root){
      m_meshes.push_back(Sphere(origin - sRadius * direction,sRadius));
    }
  //AABB computation
  computeBoneAABB();
  //Calcul de la matrice rest_pose
  m_rest_pose = glm::mat4(1.f);
  m_rest_pose = glm::translate(m_rest_pose,-m_origin);
}

/* Hierarchy functions */
Bone Bone::addChild(glm::vec3 direction, float length, float radius){
  Bone child(m_origin + m_length * m_direction, direction, length, radius, false);
  child.m_parent = this;
  child.m_path = m_path;
  child.m_path.emplace_back(m_children.size()); //We concatenate our path and add his spot
  m_children.emplace_back(child);
  return child;
}

Bone Bone::addChild(float length, float radius){
  //TODO Debugger ce feature
  Bone child(m_origin + m_length * glm::vec3(glm::vec4(m_direction,0) * m_model), m_direction, length, radius, false);
  child.m_parent = this;
  child.m_path = m_path;
  child.m_path.emplace_back(m_children.size()); //We concatenate our path and add his spot
  m_children.emplace_back(child);
  return child;
}

void Bone::addChild(Bone& child){
  child.m_parent = this;
  child.m_path = m_path;
  child.m_path.emplace_back(m_children.size()); //We concatenate our path and add his spot
  if( child.isRoot())
    child.setRoot(false);
  m_children.push_back(child);
}

Bone Bone::addChild(deque<int> path,glm::vec3 direction, float length, float radius){
  if(path.size() == 0)
    return addChild(direction, length, radius);
  int son = path[0];
  if(son >= m_children.size() || son < 0)
    return Bone();
  path.pop_front();
  return m_children[son].addChild(path, direction,length,radius);
}

void Bone::displayAABB(bool d){
  //cout << "Bone "<<m_id<< " has been set"<<endl;
  m_draw_aabb = d;
  for(auto& child : m_children){
      child.displayAABB(d);
    }
}

void Bone::setRoot(bool root){
  m_root = root;
  if(m_meshes.size() == 3){
      m_meshes.pop_back();
    }
}

/* Hierarchy  action functions */
void Bone::rotate(float theta, const glm::vec3& u){
  m_model = glm::translate(m_model,m_origin);
  m_model = glm::rotate(m_model, theta, u);
  for(auto& child : m_children){
      child.rotateFromPoint(m_model,m_origin);
    }
  m_model = glm::translate(m_model,-m_origin);
}

/* Action functions */
void Bone::rotate(const glm::mat4& R){
  m_model = glm::translate(m_model,m_origin);
  m_model = R;
  m_model = glm::translate(m_model,-m_origin);
  for(auto& child : m_children){
      child.rotateFromPoint(m_model,m_origin);
    }
}

void Bone::rotate(float angle, float x, float y, float z){
  m_model = glm::rotate(m_model, angle, glm::vec3(x,y,z));
  for(auto& child : m_children){
      child.translate(m_origin);
    }
}

void Bone::rotateFromPoint(const float angle, const glm::vec3& vec, const glm::vec3& point){
  m_model = glm::translate(m_model,point);
  m_model = glm::rotate(m_model, angle, vec);
  m_model = glm::translate(m_model,-point);
  for(auto& child : m_children){
      child.rotateFromPoint(m_model,point);
    }
}

void Bone::rotateFromPoint(const glm::mat4& R, const glm::vec3& point){
  m_model = glm::translate(m_model,point);
  m_model = R;
  m_model = glm::translate(m_model,-point);
  for(auto& child : m_children){
      child.rotateFromPoint(R,point);
    }
}
void Bone::rotateFromPoint(const float angle, float x, float y, float z, const glm::vec3& point){
  m_model = glm::translate(m_model,point);
  m_model = glm::rotate(m_model, angle, glm::vec3(x,y,z));
  m_model = glm::translate(m_model,-point);
  for(auto& child : m_children){
      child.rotateFromPoint(m_model,point);
    }
}

//virtual void rotate(const Quaternion& q);

void Bone::translate(const glm::vec3& vec){
  m_model = glm::translate(m_model, vec);
  for(auto& child : m_children){
      child.translate(m_model);
    }
}

void Bone::translate(float x, float y, float z){
  glm::vec3 tr(x,y,z);
  m_model = glm::translate(m_model, tr);
  for(auto& child : m_children){
      child.translate(m_model);
    }
}

void Bone::translate(const glm::mat4& T){
  m_model = T;
  for(auto& child : m_children){
      child.translate(T);
    }
}
//virtual void translate(const Quaternion& q);

void Bone::stretch(float length, const glm::vec3& direction){
  m_length = length;
  computeBone(m_origin,m_direction,length,m_radius,m_root);
  glm::vec3 tr(m_origin + m_length * m_direction);
  for(auto& child : m_children){
      child.translate(tr);
    }
}

//TODO Etudier la question apres un bon café
void Bone::stretch(float x, float y, float z){
  stretch(x);
}

Bone * Bone::clickOnSkeletton(Ray& r){
  if(Math::RayCast::vsOBB(r,m_aabb,m_model))
    return this;
  Bone * clicked;
  for(auto& child : m_children){
      if( (clicked = child.clickOnSkeletton(r)) != nullptr)
        return clicked;
    }
  return nullptr;
}

void Bone::pushChild( vector< Bone *>& list) {
  list.push_back(this);
  for( auto& child : m_children){
      child.pushChild(list);
    }
}

vector< Bone *> Bone::boneList(){
  vector< Bone *> list;
  list.push_back(this);
  for(auto& child : m_children){
      child.pushChild(list);
    }
  return list;
}

void Bone::computeBoneAABB() {
  glm::vec3 base1;
  glm::vec3 base2;
  Math::Algorithm::generateOrthonormalBasisFromDirection(m_direction,base1,base2);
  glm::vec3 a = m_radius * base1 + m_origin;
  glm::vec3 b = m_radius * base2 + m_origin;
  glm::vec3 c = -m_radius * base1 + m_origin;
  glm::vec3 d = -m_radius * base2 + m_origin;
  //Si c'est le root on inclut la première sphere
  if(m_root){
      a -= 0.5f * m_radius * m_direction;
      b -= 0.5f * m_radius * m_direction;
      c -= 0.5f * m_radius * m_direction;
      d -= 0.5f * m_radius * m_direction;
    }

  //+radius pour les deux spheres
  m_aabb.computeAABB(a,b,c,d,m_direction,m_length + m_radius);

}

void Bone::draw() const{

  for(const auto& mesh : m_meshes ){
      mesh.draw();
    }

  if( m_draw_aabb ){
      glLineWidth(2.0f);
      m_aabb.draw();
    }

}
