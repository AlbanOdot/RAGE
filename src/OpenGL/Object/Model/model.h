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
  virtual void translate(const float x,const  float y,const  float z);
  virtual void translate(const glm::mat4& T);
  //virtual void translate(const Quaternion& q);

  virtual void rotate(const float angle,const glm::vec3& vec);
  virtual void rotate(const float angle,const  float x,const  float y,const  float z);
  virtual void rotate(const glm::mat4 R);
  //virtual void rotate(const Quaternion& q);

  virtual void stretch(const float length, const glm::vec3& direction = glm::vec3(1,1,1));
  virtual void stretch(const float x,const  float y,const  float z);
  //On peut faire ca avec des quaternions ?

  /* Draw related stuff */
  virtual void draw() const;

  /* Accessors */
  AABB aabb()           const { return m_aabb;}
  glm::mat4 model()     const { return m_model;}
  //virtual glm::mat4* getModels() { return &m_model;}
  bool displayAABB()    const { return m_draw_aabb;}
  vector<Mesh> meshes() const {return m_meshes;}
  vector<Mesh>& meshes()      { return m_meshes;}
  string directory()    const { return m_directory;}
  //unsigned int boneCount() const { return m_meshes[0].boneCount();}
  bool animated() const { return m_animated;}
  /* Setters */
  void aabb(const AABB aabb)        { m_aabb = aabb;}
  void model(const glm::mat4 model) { m_model = model;}
  void meshes(const Mesh m)         { m_meshes.push_back(m); m_aabb.computeAABB(m_meshes);}
  virtual void displayAABB(bool d)  { m_draw_aabb = d;}
protected:
  glm::mat4 m_model;
  bool m_draw_aabb;
  bool m_dirty_model;
  bool m_animated;
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
