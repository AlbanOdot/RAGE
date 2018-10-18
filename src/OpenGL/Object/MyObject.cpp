#include "MyObject.h"
#include <gl3.h>

MyObject::MyObject(){}
MyObject::~MyObject(){}

//Mesh with ligth interaction
MyObject::MyObject(const std::vector<GLfloat>& v, const std::vector<GLfloat>& n, const std::vector<GLuint>& t) :
vertices(v),normals(n),topology(t)
{
    // Create the VAO:
    glGenVertexArrays(1, &vao);
    glBindVertexArray(vao);

    // Create the VBO for positions:;
    glGenBuffers(1, &vbo);
    glBindBuffer(GL_ARRAY_BUFFER, vbo);
    glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(GLfloat), vertices.data(), GL_STATIC_DRAW);
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(GLfloat), (GLvoid *)0);

    // Create the VBO for positions:;
    glGenBuffers(1, &nbo);
    glBindBuffer(GL_ARRAY_BUFFER, nbo);
    glBufferData(GL_ARRAY_BUFFER, normals.size() * sizeof(GLfloat), normals.data(), GL_STATIC_DRAW);
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(GLfloat), (GLvoid *)0);

    // Create the VBO for indices:
    glGenBuffers(1, &ebo);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ebo);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, topology.size()*sizeof(GLfloat), topology.data(), GL_STATIC_DRAW);

    glBindVertexArray(0);
}
//Mesh simple mesh
MyObject::MyObject(const std::vector<GLfloat>& v, const std::vector<GLuint>& t){
    MyObject(v,std::vector<GLfloat>(),t);
}
//Points cloud
MyObject::MyObject(const std::vector<GLfloat>& v){
    MyObject(v,std::vector<GLfloat>(), std::vector<GLuint>() );
}

//From points cloud to Mesh
void MyObject::addTopology(const std::vector<GLuint>& t){
    topology = t;
    glBindVertexArray(vao);
    // Create the VBO for positions:;
    glBindBuffer(GL_ARRAY_BUFFER, vbo);
    glBindBuffer(GL_ARRAY_BUFFER, nbo);
    // Create the VBO for indices:
    glGenBuffers(1, &ebo);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ebo);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, topology.size()*sizeof(GLfloat), topology.data(), GL_STATIC_DRAW);
    glBindVertexArray(0);
}
//From Mesh to Mesh with light interaction
void MyObject::addNormals(const std::vector<GLfloat>& n){
    normals = n;
    // Create the VAO:
    glBindVertexArray(vao);
    // Create the VBO for positions
    glBindBuffer(GL_ARRAY_BUFFER, vbo);
    // Create the VBO for positions:;
    glGenBuffers(1, &nbo);
    glBindBuffer(GL_ARRAY_BUFFER, nbo);
    glBufferData(GL_ARRAY_BUFFER, normals.size() * sizeof(GLfloat), normals.data(), GL_STATIC_DRAW);
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(GLfloat), (GLvoid *)0);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ebo);

    glBindVertexArray(0);
}
//From points cloud to mesh with light interaction
void MyObject::addNormalsAndTopology(const std::vector<GLfloat>&n, const std::vector<GLuint>& t){
    normals = n;
    topology = t;
    glBindVertexArray(vao);

    // Create the VBO for positions:;
    glBindBuffer(GL_ARRAY_BUFFER, vbo);

    // Create the VBO for positions:;
    glGenBuffers(1, &nbo);
    glBindBuffer(GL_ARRAY_BUFFER, nbo);
    glBufferData(GL_ARRAY_BUFFER, normals.size() * sizeof(GLfloat), normals.data(), GL_STATIC_DRAW);
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(GLfloat), (GLvoid *)0);

    // Create the VBO for indices:
    glGenBuffers(1, &ebo);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ebo);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, topology.size()*sizeof(GLfloat), topology.data(), GL_STATIC_DRAW);

    glBindVertexArray(0);
}
