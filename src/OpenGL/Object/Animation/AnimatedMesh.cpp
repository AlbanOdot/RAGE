#include "AnimatedMesh.h"
#include "./src/OpenGL/opengl_stuff.h"
#include <iostream>

AnimatedMesh::AnimatedMesh(const vector<float> vertices, const vector<float> normals, const vector<float> UV,
                           const vector<float> colors,   const vector<unsigned int> indices, const vector<float> weights, const vector<int> weight_indices)
  : Mesh(vertices,normals,UV,colors,indices), m_weights(weights),m_weight_indices(weight_indices), m_is_complete(true)
{
  setupMesh();

}

AnimatedMesh::AnimatedMesh(const vector<float> vertices, const vector<float> normals, const vector<float> UV,
                           const vector<float> colors,   const vector<unsigned int> indices)
  : Mesh(vertices,normals,UV,colors,indices), m_is_complete(false){}


void AnimatedMesh::resetMesh(const vector<float> vertices, const vector<float> normals){
  m_vertices = vertices;
  m_normals = normals;
}

void AnimatedMesh::draw() const{
  glBindVertexArray(m_VAO);
  glDrawElements(GL_TRIANGLES, m_indices.size()*sizeof(uint), GL_UNSIGNED_INT, 0);
  glBindVertexArray(0);
}

void AnimatedMesh::setupMesh(){
  setupMesh(m_vertices,m_normals);
}

void AnimatedMesh::setupMesh( const vector<float>& vertices , const vector<float>& normals){
  glGenVertexArrays(1, &m_VAO);
  glBindVertexArray(m_VAO);

  // vertex positions
  glDeleteBuffers(1,&m_VBO);
  glGenBuffers(1, &m_VBO);
  glBindBuffer(GL_ARRAY_BUFFER, m_VBO);
  glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(GLfloat), vertices.data(), GL_STATIC_DRAW);
  glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3* sizeof(GLfloat), (GLvoid*)0);
  glEnableVertexAttribArray(0);

  // normals
  glDeleteBuffers(1,&m_NBO);
  glGenBuffers(1, &m_NBO);
  glBindBuffer(GL_ARRAY_BUFFER, m_NBO);
  glBufferData(GL_ARRAY_BUFFER, normals.size() * sizeof(GLfloat), normals.data(), GL_STATIC_DRAW);
  glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 3* sizeof(GLfloat), (GLvoid *)0);
  glEnableVertexAttribArray(1);

  //Color
  glDeleteBuffers(1,&m_CRBO);
  glGenBuffers(1, &m_CRBO);
  glBindBuffer(GL_ARRAY_BUFFER, m_CRBO);
  glBufferData(GL_ARRAY_BUFFER, m_colors.size() * sizeof(GLfloat), m_colors.data(), GL_STATIC_DRAW);
  glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, 3*sizeof(GLfloat), (GLvoid *)0);
  glEnableVertexAttribArray(2);

  // vertex texture coords
  glDeleteBuffers(1,&m_UVBO);
  glGenBuffers(1, &m_UVBO);
  glBindBuffer(GL_ARRAY_BUFFER, m_UVBO);
  glBufferData(GL_ARRAY_BUFFER, m_uv.size() * sizeof(GLfloat), m_uv.data(), GL_STATIC_DRAW);
  glVertexAttribPointer(5, 2, GL_FLOAT, GL_FALSE, 2* sizeof(GLfloat), (GLvoid *)0);
  glEnableVertexAttribArray(3);

  //Weights
  glDeleteBuffers(1,&m_WBO);
  glGenBuffers(1, &m_WBO);
  glBindBuffer(GL_ARRAY_BUFFER, m_WBO);
  glBufferData(GL_ARRAY_BUFFER, m_weights.size() * sizeof(GLfloat), m_weights.data(), GL_STATIC_DRAW);
  glVertexAttribPointer(3, 4, GL_FLOAT, GL_FALSE, 4*sizeof(GLfloat), (GLvoid *)0);
  glEnableVertexAttribArray(4);

  //Corresponding bones
  glDeleteBuffers(1,&m_WIBO);
  glGenBuffers(1, &m_WIBO);
  glBindBuffer(GL_ARRAY_BUFFER, m_WIBO);
  glBufferData(GL_ARRAY_BUFFER, m_weight_indices.size() * sizeof(GLint), m_weight_indices.data(), GL_STATIC_DRAW);
  glVertexAttribPointer(4, 4, GL_INT, GL_FALSE, 4*sizeof(GLint), (GLvoid *)0);
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

void AnimatedMesh::attachWeights(const vector<float> weights, const vector<int> weight_indices){
  m_weights = weights;
  m_weight_indices = weight_indices;
  if( !m_normals.empty() ) //Random buffer from Mesh
    setupMesh();
}

void AnimatedMesh::transformMesh(const vector<glm::mat4>& transfo, const vector<glm::mat4>& invRestPose){

  vector<float> new_vertex;
  vector<float> new_normal;

  for(unsigned int i = 0; i < (m_vertices.size() / 3); ++i){//Autant de vertice que de normales
      glm::vec4 vertex(m_vertices[3*i],m_vertices[3*i+1],m_vertices[3*i+2],1.f);
      glm::vec4 normal(m_normals[3*i],m_normals[3*i+1], m_normals[3*i+2],0.f);
      glm::vec4 weights(m_weights[4*i],m_weights[4*i+1],m_weights[4*i+2],m_weights[4*i+3]);
      glm::vec4 weights_indices(m_weight_indices[4*i],m_weight_indices[4*i+1],m_weight_indices[4*i+2],m_weight_indices[4*i+3]);

      vertex =   vertex * (weights.x * transfo[weights_indices.x] * invRestPose[weights_indices.x]
          + weights.y * transfo[weights_indices.y] * invRestPose[weights_indices.y]
          + weights.z * transfo[weights_indices.z] * invRestPose[weights_indices.z]
          + weights.w * transfo[weights_indices.w] * invRestPose[weights_indices.w]);
      new_vertex.push_back(vertex.x);new_vertex.push_back(vertex.y);new_vertex.push_back(vertex.z);
      if( i == 3023){
          cout << "weights_indices : ("<<weights_indices.x<<","<<weights_indices.y<<","<<weights_indices.z<<","<<weights_indices.w<<")"<<endl;
          cout << "weights : ("<<weights.x<<","<<weights.y<<","<<weights.z<<","<<weights.w<<")"<<endl;
          cout << "new vertex : ("<<vertex.x<<","<<vertex.y<<","<<vertex.z<<")"<<endl;
          cout << "old vertex : ("<<m_vertices[3*i]<<","<<m_vertices[3*i+1]<<","<<m_vertices[3*i+2]<<")"<<endl;
        }
      normal =   normal * (weights.x * transfo[weights_indices.x] * invRestPose[weights_indices.x]
          + weights.y * transfo[weights_indices.y] * invRestPose[weights_indices.y]
          + weights.z * transfo[weights_indices.z] * invRestPose[weights_indices.z]
          + weights.w * transfo[weights_indices.w] * invRestPose[weights_indices.w]);
      normal = glm::normalize(normal);
      new_normal.push_back(normal.x);new_normal.push_back(normal.y);new_normal.push_back(normal.z);
    }

  setupMesh(new_vertex,new_normal);

}

