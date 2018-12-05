#include "Bone.h"
#include <iostream>
#include "./src/Math/Algorithm.h"
#include "./src/OpenGL/Object/Shapes/shapes.h"
#include <random>

unsigned int Bone::m_bone_count = 0;

Bone::Bone(glm::vec3 origin , glm::vec3 direction, float length , float radius, bool root )
  : Model(), m_id(m_bone_count++), m_root(root), m_origin(origin), m_direction(glm::normalize(direction)), m_length(length), m_radius(radius)
{
  computeBone(origin,direction,length,radius,root);
}


void Bone::computeBone(glm::vec3 origin , glm::vec3 direction, float length , float radius, bool root ){
  direction = glm::normalize(direction);
  m_meshes.push_back(Cristal(origin,direction,length,radius));
  float sRadius = 0.25f * m_radius;
  m_meshes.push_back(Sphere(origin + (length + sRadius*0.5f) * direction, sRadius ));
  if(root){
      m_meshes.push_back(Sphere(origin - sRadius * direction,sRadius));
    }
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
  if(m_draw_aabb){
      m_aabb.draw();
    }
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
  m_model = glm::translate(m_model,-m_origin);
  for(auto& child : m_children){
      child.rotate(m_model);
    }
}

/* Action functions */
void Bone::rotate(const glm::mat4 R){
  m_model = glm::translate(m_model,m_origin);
  m_model = R;
  m_model = glm::translate(m_model,-m_origin);
  for(auto& child : m_children){
      child.rotate(m_model);
    }
}

void Bone::rotate(float angle, float x, float y, float z){
  m_model = glm::rotate(m_model, angle, glm::vec3(x,y,z));
  for(auto& child : m_children){
      child.rotate(m_model);
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
  if(Math::RayCast::vsAABB(r,m_aabb))
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
