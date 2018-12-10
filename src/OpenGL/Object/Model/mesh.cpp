#include "mesh.h"
#include "./src/OpenGL/opengl_stuff.h"
#include <iostream>

Mesh::Mesh(const vector<float> vertices, const vector<float> normals, const vector<float> UV,
           const vector<float> colors,   const vector<unsigned int> indices)
  : m_vertices(vertices), m_normals(normals), m_uv(UV), m_colors(colors), m_indices(indices)
{
  cout << "   Number of vertices : "<< m_vertices.size() / 3 <<endl;
  cout << "   Number of normals  : "<<m_normals.size() / 3   << endl;
  cout << "   Number of UV       : "<<m_uv.size() / 2        << endl;
  cout << "   Number of colors   : "<< m_colors.size() / 3   << endl;
  cout << "   Number of faces    : "<< m_indices.size() / 3  << endl;
  setupMesh();
}

void Mesh::draw() const{
  glBindVertexArray(m_VAO);
  glDrawElements(GL_TRIANGLES, m_indices.size()*sizeof(uint), GL_UNSIGNED_INT, 0);
  glBindVertexArray(0);
}

void Mesh::setupMesh(){
  glGenVertexArrays(1, &m_VAO);
  glBindVertexArray(m_VAO);

  // vertex positions
  glGenBuffers(1, &m_VBO);
  glBindBuffer(GL_ARRAY_BUFFER, m_VBO);
  glBufferData(GL_ARRAY_BUFFER, m_vertices.size() * sizeof(GLfloat), m_vertices.data(), GL_STATIC_DRAW);
  glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3* sizeof(GLfloat), (GLvoid*)0);
  glEnableVertexAttribArray(0);

  // normals
  glGenBuffers(1, &m_NBO);
  glBindBuffer(GL_ARRAY_BUFFER, m_NBO);
  glBufferData(GL_ARRAY_BUFFER, m_normals.size() * sizeof(GLfloat), m_normals.data(), GL_STATIC_DRAW);
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

  glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_EBO);
  glBufferData(GL_ELEMENT_ARRAY_BUFFER, m_indices.size() * sizeof(unsigned int),m_indices.data(), GL_STATIC_DRAW);

  glBindVertexArray(0);
}

Mesh::Mesh(){
  glGenVertexArrays(1, &m_VAO);
  glGenBuffers(1, &m_VBO);
  glGenBuffers(1, &m_NBO);
  glGenBuffers(1, &m_CRBO);
  glGenBuffers(1, &m_UVBO);
  glGenBuffers(1, &m_EBO);
}

void Mesh::resetMesh(){
  m_vertices.clear();
  m_normals.clear();
  m_uv.clear();
  m_colors.clear();
  m_indices.clear();
}
