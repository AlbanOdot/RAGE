#ifndef SHAPES_H
#define SHAPES_H

/*
 *
 *
 * Include this file whenever you have multiple shapes files to include
 *
 *
 */
#include "src/OpenGL/Object/Shapes/Cristal.h"
#include "src/OpenGL/Object/Shapes/Cube.h"
#include "src/OpenGL/Object/Shapes/Cylinder.h"
#include "src/OpenGL/Object/Shapes/Shape.h"
#include "src/OpenGL/Object/Shapes/Sphere.h"
#include "src/OpenGL/Object/Shapes/Tetrahedron.h"
#include "./src/OpenGL/opengl_stuff.h"

typedef struct _quad{
  std::vector<GLfloat> vertices = {-1.0,-1.0,
                                   1.f,-1.0,
                                   1.0, 1.0,
                                   -1.0, 1.0};
  std::vector<GLfloat> uv = {0.0,0.0,
                             1.0,0.0,
                             1.0,1.0,
                             0.0,1.0};

  std::vector<GLuint> indices = {0,1,2,
                                 0,2,3};
  GLuint vao;
  GLuint vbo;
  GLuint ebo;
  GLuint uvbo;
  void quadLoad() {
    // Create the VAO:
    if(!vao)
      glGenVertexArrays(1, &vao);
    glBindVertexArray(vao);
    unsigned int i = 0;
    // Create the VBO for positions:;
    glDeleteBuffers(1,&vbo);//ne raise pas d'erreur si le buffer existe pas
    glGenBuffers(1, &vbo);
    glBindBuffer(GL_ARRAY_BUFFER, vbo);
    glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(GLfloat), vertices.data(), GL_STATIC_DRAW);
    glVertexAttribPointer(i, 3, GL_FLOAT, GL_FALSE, 2*sizeof(GLfloat), (GLvoid *)0);
    glEnableVertexAttribArray(i++);

    //IF TEXCOORDS IS EMPTY FILL IT WITH ZEROS
    // Create the UVO for textures;
    glDeleteBuffers(1,&uvbo);
    glGenBuffers(1, &uvbo);
    glBindBuffer(GL_ARRAY_BUFFER, uvbo);
    glBufferData(GL_ARRAY_BUFFER, uv.size() * sizeof(GLfloat), uv.data(), GL_STATIC_DRAW);
    glVertexAttribPointer(i, 2, GL_FLOAT, GL_FALSE, 2*sizeof(GLfloat), (GLvoid *)0);
    glEnableVertexAttribArray(i++);

    //From here we suppose that vertex indices, normal indices are in the same order
    // Create the EBO for topology:
    glDeleteBuffers(1, &ebo);
    glGenBuffers(1, &ebo);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ebo);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices.size()*sizeof(GLuint), indices.data(), GL_STATIC_DRAW);

    glBindVertexArray(0);
  }

  void quadDraw(){
    glBindVertexArray(vao);
    glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
    glBindVertexArray(0);
  }

} Quad;
#endif // SHAPES_H
