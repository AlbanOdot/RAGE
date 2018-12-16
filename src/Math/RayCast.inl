#include "RayCast.h"
#define GLM_ENABLE_EXPERIMENTAL
#include <glm/gtx/intersect.hpp>
#include <iostream>

/* Compute the instersection between a ray and the AABB of an object */
bool Math::RayCast::vsAABB(const Ray& r, const AABB& aabb){
  Mesh box = aabb.box();
  bool intersect = false;
  glm::vec3 intersectionPosition;
  for(unsigned int i = 0; !intersect && i< box.m_indices.size() - 2; i += 3){
      glm::vec3 a(box.m_vertices[box.m_indices[i ] ],box.m_vertices[box.m_indices[i  ] +1],box.m_vertices[box.m_indices[i  ] +2]);
      glm::vec3 b(box.m_vertices[box.m_indices[i+1]],box.m_vertices[box.m_indices[i+1] +1],box.m_vertices[box.m_indices[i+1] +2]);
      glm::vec3 c(box.m_vertices[box.m_indices[i+2]],box.m_vertices[box.m_indices[i+2] +1],box.m_vertices[box.m_indices[i+2] +2]);
      intersect = glm::intersectLineTriangle(r.m_o,r.m_d,a,b,c,intersectionPosition);
    }
  return intersect;
}

bool Math::RayCast::vsOBB(const Ray& r, const AABB& aabb, const glm::mat4& model){
  Mesh box = aabb.box();
  bool intersect = false;
  glm::vec3 intersectionPosition;
  for(unsigned int i = 0; !intersect && i< box.m_indices.size() - 2; i += 3){
      glm::vec3 a(box.m_vertices[box.m_indices[i ] ],box.m_vertices[box.m_indices[i  ] +1],box.m_vertices[box.m_indices[i  ] +2]);
      glm::vec3 b(box.m_vertices[box.m_indices[i+1]],box.m_vertices[box.m_indices[i+1] +1],box.m_vertices[box.m_indices[i+1] +2]);
      glm::vec3 c(box.m_vertices[box.m_indices[i+2]],box.m_vertices[box.m_indices[i+2] +1],box.m_vertices[box.m_indices[i+2] +2]);
      intersect = glm::intersectLineTriangle(r.m_o,r.m_d, glm::vec3(model * glm::vec4(a,1.f)),glm::vec3(model * glm::vec4(b,1.f)),
                                             glm::vec3(model * glm::vec4(c,1.f)),intersectionPosition);
    }
  return intersect;
}

/* Compute the intersection between a ray and a triangle */
bool Math::RayCast::vsTriangle(const Ray& r, const glm::vec3& a, const glm::vec3& b, const glm::vec3& c){
  glm::vec3 intersectionPosition;
  return glm::intersectLineTriangle(r.m_o,r.m_d,a,b,c,intersectionPosition);
}

/* Compute the intersection between a ray and a triangle and store it in intersectionPosition*/
bool Math::RayCast::vsTriangle(const Ray& r, const glm::vec3& a, const glm::vec3& b,
                               const glm::vec3& c, glm::vec3& intersectionPosition){
  return glm::intersectLineTriangle(r.m_o,r.m_d,a,b,c,intersectionPosition);
}


/* Compute the intersection between a ray and a mesh */
bool Math::RayCast::vsMesh( const Mesh& mesh);

/* Compute the intersection between a ray and a plane */
bool Math::RayCast::vsPlane(const Ray& r, const glm::vec3 a, const glm::vec3& normal, glm::vec3& res){
  float dist;
  if(glm::intersectRayPlane(r.m_o,r.m_d,a,normal,dist)){
      res = r.m_o + dist * r.m_d;
      return true;
  }
  return false;

}

/* Compute the intersection between a ray and a cylinder */
bool Math::RayCast::vsCylinder(const Ray& r, const glm::vec3& a, glm::vec3& b, float radius);
