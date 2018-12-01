#include "Cube.h"
#include <iostream>
#include "../../opengl_stuff.h"
Cube::Cube() : Shape(CUBE){}

Cube::Cube(glm::vec3 min, glm::vec3 max) : Shape(CUBE){
  computeCube(min,max);
}

Cube::Cube(glm::vec3 a,glm::vec3 b,glm::vec3 c,glm::vec3 d,glm::vec3 dir,float length) : Shape(CUBE){
  computeCube(a,b,c,d,dir,length);
}

void Cube::computeCube(glm::vec3 min, glm::vec3 max){
  //left face
  m_topLeftFront = glm::vec3(min.x,max.y,max.z);
  m_botLeftFront = glm::vec3(min.x,min.y,max.z);
  m_topLeftBack =  glm::vec3(min.x,max.y,min.z);
  m_botLeftBack =  glm::vec3(min.x,min.y,min.z);
  //right face
  m_topRightFront = glm::vec3(max.x,max.y,max.z);
  m_botRightFront = glm::vec3(max.x,min.y,max.z);
  m_topRightBack =  glm::vec3(max.x,max.y,min.z);
  m_botRightBack =  glm::vec3(max.x,min.y,min.z);

  /*
   *          0-----3
   *          |     |
   *          |     |     Top
   *          1-----2
   */
  Point3(m_topLeftBack);Point3(m_topLeftFront);Point3(m_topRightFront);Point3(m_topRightBack);
  /*
   *          4-----7
   *          |     |
   *          |     |     Bottom
   *          5-----6
   */
  Point3(m_botLeftBack);Point3(m_botLeftFront);Point3(m_botRightFront);Point3(m_botRightBack);

  Normal(glm::normalize(m_topLeftBack));Normal(glm::normalize(m_topLeftFront));Normal(glm::normalize(m_topRightFront));Normal(glm::normalize(m_topRightBack));
  Normal(glm::normalize(m_botLeftBack));Normal(glm::normalize(m_botLeftFront));Normal(glm::normalize(m_botRightFront));Normal(glm::normalize(m_botRightBack));
  Colors(0.,0.,0.);Colors(0.,0.,0.);Colors(0.,0.,0.);Colors(0.,0.,0.);
  Colors(0.,0.,0.);Colors(0.,0.,0.);Colors(0.,0.,0.);Colors(0.,0.,0.);
  Point2(glm::normalize(m_topLeftBack));Point2(glm::normalize(m_topLeftFront));Point2(glm::normalize(m_topRightFront));Point2(glm::normalize(m_topRightBack));
  Point2(glm::normalize(m_botLeftBack));Point2(glm::normalize(m_botLeftFront));Point2(glm::normalize(m_botRightFront));Point2(glm::normalize(m_botRightBack));
  //TOP
  Triangle(0,1,2);
  Triangle(0,2,3);
  //FRONT
  Triangle(1,6,2);
  Triangle(1,5,6);
  //BOTTOM
  Triangle(6,5,7);
  Triangle(7,5,4);
  //LEFT
  Triangle(1,0,5);
  Triangle(0,4,5);
  //BACK
  Triangle(0,3,4);
  Triangle(3,7,4);
  //RIGHT
  Triangle(3,2,6);
  Triangle(3,6,7);

  setupMesh();
}

void Cube::draw() const{
  glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
  glBindVertexArray(m_VAO);
  glDrawElements(GL_TRIANGLES, m_indices.size()*sizeof(uint), GL_UNSIGNED_INT, 0);
  glBindVertexArray(0);
  glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
}

void Cube::computeCube(glm::vec3 a,glm::vec3 b,glm::vec3 c,glm::vec3 d,glm::vec3 dir,float length){
  //TODO Faire un cube de tout ce bordel

  //left face
  m_topLeftFront = a;
  m_botLeftFront = b;
  m_topLeftBack =  d;
  m_botLeftBack =  c;
  //right face
  m_topRightFront = a + dir * length;
  m_botRightFront = b + dir * length;
  m_topRightBack =  d + dir*length;
  m_botRightBack =  c + dir * length;

  /*
   *          0-----3
   *          |     |
   *          |     |     Top
   *          1-----2
   */
  Point3(m_topLeftBack);Point3(m_topLeftFront);Point3(m_topRightFront);Point3(m_topRightBack);
  /*
   *          4-----7
   *          |     |
   *          |     |     Bottom
   *          5-----6
   */
  Point3(m_botLeftBack);Point3(m_botLeftFront);Point3(m_botRightFront);Point3(m_botRightBack);

  Normal(glm::normalize(m_topLeftBack));Normal(glm::normalize(m_topLeftFront));Normal(glm::normalize(m_topRightFront));Normal(glm::normalize(m_topRightBack));
  Normal(glm::normalize(m_botLeftBack));Normal(glm::normalize(m_botLeftFront));Normal(glm::normalize(m_botRightFront));Normal(glm::normalize(m_botRightBack));
  Colors(0.,0.,0.);Colors(0.,0.,0.);Colors(0.,0.,0.);Colors(0.,0.,0.);
  Colors(0.,0.,0.);Colors(0.,0.,0.);Colors(0.,0.,0.);Colors(0.,0.,0.);
  Point2(glm::normalize(m_topLeftBack));Point2(glm::normalize(m_topLeftFront));Point2(glm::normalize(m_topRightFront));Point2(glm::normalize(m_topRightBack));
  Point2(glm::normalize(m_botLeftBack));Point2(glm::normalize(m_botLeftFront));Point2(glm::normalize(m_botRightFront));Point2(glm::normalize(m_botRightBack));
  //TOP
  Triangle(0,1,2);
  Triangle(0,2,3);
  //FRONT
  Triangle(1,6,2);
  Triangle(1,5,6);
  //BOTTOM
  Triangle(6,5,7);
  Triangle(7,5,4);
  //LEFT
  Triangle(1,0,5);
  Triangle(0,4,5);
  //BACK
  Triangle(0,3,4);
  Triangle(3,7,4);
  //RIGHT
  Triangle(3,2,6);
  Triangle(3,6,7);

  setupMesh();
}
