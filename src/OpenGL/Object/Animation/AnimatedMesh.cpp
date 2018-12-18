#include "AnimatedMesh.h"
#include <iostream>
#include <omp.h>
#include "./src/OpenGL/opengl_stuff.h"
#include "./src/Math/Quaternion.h"

AnimatedMesh::AnimatedMesh(const vector<float> vertices, const vector<float> normals, const vector<float> UV,
                           const vector<float> colors,   const vector<unsigned int> indices)
{
  m_vertices = std::move(vertices);
  m_normals = std::move(normals);
  m_uv = std::move(UV);
  m_colors = std::move(colors);
  m_indices = std::move(indices);
  //Si on a pas de poids on met tout à 0
  m_weight_indices.resize(2*m_uv.size());
  m_weights.resize(2*m_uv.size());
  //#pragma omp for
  for(unsigned long i = 0; i < 2*m_uv.size(); ++i){
      m_weight_indices[i] = 0;
      m_weights[i] = 0.f;
    }
  setupMesh();
}

AnimatedMesh::AnimatedMesh(const Mesh& m)
{
  m_vertices = std::move(m.m_vertices);
  m_normals = std::move(m.m_normals);
  m_uv = std::move(m.m_uv);
  m_colors = std::move(m.m_colors);
  m_indices = std::move(m.m_indices);
  //Si on a pas de poids on met tout à 0
  m_weight_indices.resize(2*m_uv.size());
  m_weights.resize(2*m_uv.size());
  //#pragma omp for
  for(unsigned long i = 0; i < 2*m_uv.size(); ++i){
      m_weight_indices[i] = 0;
      m_weights[i] = 0.f;
    }
  setupMesh();
}

void AnimatedMesh::setupMesh(){
  setupMesh(m_vertices,m_normals);
}

void AnimatedMesh::setupMesh( const vector<float> vertices , const vector<float> normals){
  glGenVertexArrays(1, &m_VAO);
  glBindVertexArray(m_VAO);

  // vertex positions
  glGenBuffers(1, &m_VBO);
  glBindBuffer(GL_ARRAY_BUFFER, m_VBO);
  glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(GLfloat), vertices.data(), GL_STATIC_DRAW);
  glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3* sizeof(GLfloat), (GLvoid*)0);
  glEnableVertexAttribArray(0);

  // normals
  glGenBuffers(1, &m_NBO);
  glBindBuffer(GL_ARRAY_BUFFER, m_NBO);
  glBufferData(GL_ARRAY_BUFFER, normals.size() * sizeof(GLfloat), normals.data(), GL_STATIC_DRAW);
  glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 3* sizeof(GLfloat), (GLvoid *)0);
  glEnableVertexAttribArray(1);

  //Color
  glGenBuffers(1, &m_CRBO);
  glBindBuffer(GL_ARRAY_BUFFER, m_CRBO);
  glBufferData(GL_ARRAY_BUFFER, m_colors.size() * sizeof(GLfloat), m_colors.data(), GL_STATIC_DRAW);
  glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, 3*sizeof(GLfloat), (GLvoid *)0);
  glEnableVertexAttribArray(2);

  // vertex texture coords
  glGenBuffers(1, &m_UVBO);
  glBindBuffer(GL_ARRAY_BUFFER, m_UVBO);
  glBufferData(GL_ARRAY_BUFFER, m_uv.size() * sizeof(GLfloat), m_uv.data(), GL_STATIC_DRAW);
  glVertexAttribPointer(3, 2, GL_FLOAT, GL_FALSE, 2* sizeof(GLfloat), (GLvoid *)0);
  glEnableVertexAttribArray(3);

  //Weights
  glGenBuffers(1, &m_WBO);
  glBindBuffer(GL_ARRAY_BUFFER, m_WBO);
  glBufferData(GL_ARRAY_BUFFER, m_weights.size() * sizeof(GLfloat), m_weights.data(), GL_STATIC_DRAW);
  glVertexAttribPointer(4, 4, GL_FLOAT, GL_FALSE, 4*sizeof(GLfloat), (GLvoid *)0);
  glEnableVertexAttribArray(4);

  //Corresponding bones
  glGenBuffers(1, &m_WIBO);
  glBindBuffer(GL_ARRAY_BUFFER, m_WIBO);
  glBufferData(GL_ARRAY_BUFFER, m_weight_indices.size() * sizeof(GLfloat), m_weight_indices.data(), GL_STATIC_DRAW);
  glVertexAttribPointer(5, 4, GL_FLOAT, GL_FALSE, 4*sizeof(GLfloat), (GLvoid *)0);
  glEnableVertexAttribArray(5);

  glGenBuffers(1, &m_EBO);
  glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_EBO);
  glBufferData(GL_ELEMENT_ARRAY_BUFFER, m_indices.size() * sizeof(unsigned int),m_indices.data(), GL_STATIC_DRAW);

  glBindVertexArray(0);
}

AnimatedMesh::AnimatedMesh() : Mesh(), m_is_complete(false){
  glGenBuffers(1, &m_WBO);
  glGenBuffers(1, &m_WIBO);
}

void AnimatedMesh::attachWeights(const vector<float> weights, const vector<float> weight_indices){
  m_weights = weights;
  m_weight_indices = weight_indices;
  if( !m_normals.empty() ) //Random buffer from Mesh
    setupMesh();
}


void AnimatedMesh::transformMesh(const vector<glm::mat4>& transfo){

  vector<float> new_vertex;
  new_vertex.resize(m_vertices.size());
  vector<float> new_normal;
  new_normal.resize(m_normals.size());

  #pragma omp for
  for(unsigned int i = 0; i < (m_vertices.size() / 3); ++i){//Autant de vertice que de normales
      uint x = 3*i; uint y = 3*i+1; uint z = 3*i+2;
      uint r = 4*i; uint g = 4*i+1; uint b = 4*i+2; uint a = 4*i +3;
      glm::vec4 vertex(m_vertices[x],m_vertices[y],m_vertices[z],1.f);
      glm::vec4 normal(m_normals[x],m_normals[y], m_normals[z],0.f);
      glm::vec4 weights(m_weights[r],m_weights[g],m_weights[b],m_weights[a]);
      glm::vec4 weights_indices(m_weight_indices[r],m_weight_indices[g],m_weight_indices[b],m_weight_indices[a]);

      glm::mat4 T =  weights.x * transfo[weights_indices.x] //* invRestPose[weights_indices.x]
          + weights.y * transfo[weights_indices.y] //* invRestPose[weights_indices.y]
          + weights.z * transfo[weights_indices.z] //* invRestPose[weights_indices.z]
          + weights.w * transfo[weights_indices.w];// * invRestPose[weights_indices.w]);
      vertex = T * vertex;
      new_vertex[x] = vertex.x; new_vertex[y] = vertex.y; new_vertex[z] = vertex.z;
      normal = glm::normalize( T * normal);
      new_normal[x] = normal.x;new_normal[y] = normal.y;new_normal[z] = normal.z;

    }

  setupMesh(new_vertex,new_normal);

}

void AnimatedMesh::transformMesh(const vector<Math::DualQuaternion>& quats){

  vector<float> new_vertex;
  new_vertex.resize(m_vertices.size());
  vector<float> new_normal;
  new_normal.resize(m_normals.size());

  #pragma omp for
  for(unsigned int i = 0; i < (m_vertices.size() / 3); ++i){//Autant de vertice que de normales
      uint x = 3*i; uint y = 3*i+1; uint z = 3*i+2;
      uint r = 4*i; uint g = 4*i+1; uint b = 4*i+2; uint a = 4*i +3;
      glm::vec3 vertex(m_vertices[x],m_vertices[y],m_vertices[z]);
      glm::vec3 normal(m_normals[x],m_normals[y], m_normals[z]);
      glm::vec4 weights(m_weights[r],m_weights[g],m_weights[b],m_weights[a]);
      glm::vec4 weights_indices(m_weight_indices[r],m_weight_indices[g],m_weight_indices[b],m_weight_indices[a]);

      //On blend les quaternions
      Math::Quaternion q0 = quats[weights_indices.x].rotation();
      Math::DualQuaternion Q =  quats[weights_indices.x] * weights.x;
      Q = Q + ( q0.dot(quats[weights_indices.y].rotation()) > 0 ? quats[weights_indices.y] * weights.y : quats[weights_indices.y] * weights.y * -1.f);
      Q = Q + ( q0.dot(quats[weights_indices.z].rotation()) > 0 ? quats[weights_indices.z] * weights.z : quats[weights_indices.z] * weights.z * -1.f);
      Q = Q + ( q0.dot(quats[weights_indices.w].rotation()) > 0 ? quats[weights_indices.w] * weights.w : quats[weights_indices.w] * weights.w * -1.f);
      vertex = Q.transform(vertex);
      new_vertex[x] = vertex.x; new_vertex[y] = vertex.y; new_vertex[z] = vertex.z;
      normal = Q.rotate(normal);
      new_normal[x] = normal.x;new_normal[y] = normal.y;new_normal[z] = normal.z;
    }

  setupMesh(new_vertex,new_normal);
}
