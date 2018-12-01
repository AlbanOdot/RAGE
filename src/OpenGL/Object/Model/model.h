#ifndef Model_H
#define Model_H
#include <string>
#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>
#include <glm/mat4x4.hpp>

#include "Mesh.h"
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
  virtual ~Model();
  //Load a mesh from a file
  Model(string path){loadModel(path);}

  /* ROTATION AND MODEL CHANGE STUF */
  virtual void translate(const glm::vec3& vec);
  virtual void translate(float x, float y, float z);
  //virtual void translate(const Quaternion& q);

  virtual void rotate(float angle, const glm::vec3& vec);
  virtual void rotate(const glm::mat4& R);
  //virtual void rotate(const Quaternion& q);

  virtual void stretch(float length, const glm::vec3& direction = glm::vec3(1,1,1));
  virtual void stretch(float x = 1.f, float y = 1.f, float z = 1.f);
  //On peut faire ca avec des quaternions ?

  /* Draw related stuff */
  virtual void draw() const;
  virtual void displayAABB(bool d) { m_draw_aabb = d;}

  /* Accessors */
  AABB aabb()           const { return m_aabb;}
  glm::mat4 model()     const { return m_model;}
  bool displayAABB()    const { return m_draw_aabb;}
  vector<Mesh> meshes() const {return m_meshes;}
  vector<Mesh>& meshes()      { return m_meshes;}
  string directory()    const { return m_directory;}
  /* Setters */
  void aabb(const AABB aabb)        { m_aabb = aabb;}
  void model(const glm::mat4 model) { m_model = model;}
  void meshes(const Mesh m)         { m_meshes.push_back(m); m_aabb.computeAABB(m_meshes);}
  void showAABB(bool display)       { m_draw_aabb = display;}
protected:
  glm::mat4 m_model;
  bool m_draw_aabb;
  bool m_dirty_model;
  vector<Mesh> m_meshes;
  AABB m_aabb;
  string m_directory;
private:

  /*  Functions   */
  void loadModel(const string path);
  void processNode(aiNode *node, const aiScene *scene);
  Mesh processMesh(aiMesh *mesh);
  //vector<Texture> loadMaterialTextures(aiMaterial *mat, aiTextureType type,string typeName);
};

#endif // Model_H
