#include "AABB.h"
#include "../../opengl_stuff.h"
AABB::AABB() {}

AABB::AABB(std::vector<Mesh> meshes){
  computeAABB(meshes);
}
AABB::AABB(const glm::vec3& min, const glm::vec3& max){
  m_box.computeCube(min,max);
}

void AABB::computeAABB(std::vector<Mesh> meshes){
  glm::vec3 m_min = glm::vec3(meshes[0].m_vertices[0],meshes[0].m_vertices[1],meshes[0].m_vertices[2]);
  glm::vec3 m_max = glm::vec3(meshes[0].m_vertices[0],meshes[0].m_vertices[1],meshes[0].m_vertices[2]);
  for(const auto& mesh : meshes){
      for(unsigned int i = 0; i < mesh.m_vertices.size() - 2; i += 3){

          m_min.x = mesh.m_vertices[i] < m_min.x ? mesh.m_vertices[i] : m_min.x;
          m_min.y = mesh.m_vertices[i+1] < m_min.y ? mesh.m_vertices[i+1] : m_min.y;
          m_min.z = mesh.m_vertices[i+2] < m_min.z ? mesh.m_vertices[i+2] : m_min.z;

          m_max.x = mesh.m_vertices[i] > m_max.x ? mesh.m_vertices[i] : m_max.x;
          m_max.y = mesh.m_vertices[i+1] > m_max.y ? mesh.m_vertices[i+1] : m_max.y;
          m_max.z = mesh.m_vertices[i+2] > m_max.z ? mesh.m_vertices[i+2] : m_max.z;
        }
    }
    m_box.computeCube(m_min,m_max);
}

void AABB::draw() const{
  glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
  m_box.draw();
  glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
}

void AABB::computeAABB(glm::vec3 a,glm::vec3 b,glm::vec3 c,glm::vec3 d,glm::vec3 dir,float length){
  m_box.computeCube(a,b,c,d,dir,length);
}
