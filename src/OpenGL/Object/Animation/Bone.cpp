#include "Bone.h"
#include <iostream>
#include "./src/Math/Algorithm.h"
#include "./src/OpenGL/Object/Shapes/shapes.h"
#include <random>

unsigned int Bone::m_bone_count = 0;

Bone::Bone(glm::vec3 origin , glm::vec3 direction, float length , float radius )
  : Model(), m_id(m_bone_count++), m_root(true), m_origin(origin), m_direction(glm::normalize(direction)), m_length(length), m_radius(radius)
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

void Bone::showAABB(bool d){
  cout << "Bone "<<m_id<< " has been set"<<endl;
  m_draw_aabb = d;
  for(auto& child : m_children){
      child.showAABB(d);
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
void Bone::rotate(float theta, const glm::vec3& u){
  //m_model = glm::translate(m_model,-m_origin);
  m_model = glm::rotate(m_model, theta, u);
  //m_model = glm::translate(m_model,m_origin);
  for(auto& child : m_children){
      child.rotate(m_model);
    }
}
//void rotate(Quaternion q);
//void stretch(glm::vec3 direction, float length);

/* Action functions */
void Bone::rotate(const glm::mat4& R){
  m_model = R;
  for(auto& child : m_children){
      child.rotate(R);
    }
}
//void rotateLocal(float theta);
//void rotateLocal(Quaternion q);
