#ifndef Model_H
#define Model_H
#include <string>
#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>
#include <glm/mat4x4.hpp>

#include "src/OpenGL/Object/Model/AABB.h"


/*
 *
 *
 * Inherit this one if you need a mesh with a model matrix
 *
 *
*/


class Model
{
public:
  /* Constructors n shiet */
  Model();
  Model(Shape s);
  virtual ~Model();

  /* ROTATION AND MODEL CHANGE STUF */
  virtual void translate(const glm::vec3& vec)=0;
  virtual void translate(const float x,const  float y,const  float z)=0;
  virtual void translate(const glm::mat4& T) = 0;
  //virtual void translate(const Quaternion&  q);

  virtual void rotate(const float angle,const glm::vec3& vec) = 0;
  virtual void rotate(const float angle,const  float x,const  float y,const  float z) = 0;
  virtual void rotate(const glm::mat4& R) = 0;
  //virtual void rotate(const Quaternion& q);

  virtual void stretch(const float length, const glm::vec3& direction = glm::vec3(1,1,1)) = 0;
  virtual void stretch(const float x,const  float y,const  float z) = 0;
  //On peut faire ca avec des quaternions ?

  /* Draw related stuff */
  virtual void draw() const = 0;

  /* Accessors */
  AABB aabb()           const { return m_aabb;}
  glm::mat4 model()     const { return m_model;}
  bool displayAABB()    const { return m_draw_aabb;}
  string directory()    const { return m_directory;}
  /* Setters */
  void aabb(const AABB aabb)        { m_aabb = aabb;}
  void model(const glm::mat4& model) { m_model = model;}
  virtual void displayAABB(bool d)  { m_draw_aabb = d;}
protected:
  glm::mat4 m_model;
  bool m_draw_aabb;
  bool m_dirty_model;
  AABB m_aabb;
  string m_directory;
  string getFileName(const string& s) {
    size_t i = s.rfind('/', s.length());
    if (i != string::npos)
      return(s.substr(i+1, s.length() - i));
    return("");
  }

};

#endif // Model_H
