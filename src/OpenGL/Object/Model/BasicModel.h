#ifndef BASICMODEL_H
#define BASICMODEL_H
#include "Model.h"

class BasicModel : public Model
{
public:
  BasicModel();
  //Load a mesh from a file
  BasicModel(string path){loadModel(path);}
  BasicModel(const Shape& s);

  /* ROTATION AND MODEL CHANGE STUF */
  virtual void translate(const glm::vec3& vec);
  virtual void translate(const float x,const  float y,const  float z);
  virtual void translate(const glm::mat4& T);
  //virtual void translate(const Quaternion& q);

  virtual void rotate(const float angle,const glm::vec3& vec);
  virtual void rotate(const float angle,const  float x,const  float y,const  float z);
  virtual void rotate(const glm::mat4& R);
  //virtual void rotate(const Quaternion& q);

  virtual void stretch(const float length, const glm::vec3& direction = glm::vec3(1,1,1));
  virtual void stretch(const float x,const  float y,const  float z);
  //On peut faire ca avec des quaternions ?

  /* Draw related stuff */
  virtual void draw() const;
  vector<Mesh> meshes() const {return m_meshes;}
  vector<Mesh>& meshes()      { return m_meshes;}
  void meshes(const Mesh m)         { m_meshes.push_back(m); m_aabb.computeAABB(m_meshes);}
protected:
  vector<Mesh> m_meshes;

private:
  /*  Functions   */
  void loadModel(const string path);
  void processNode(aiNode *node, const aiScene *scene);
  Mesh processMesh(aiMesh *mesh);
  //vector<Texture> loadMaterialTextures(aiMaterial *mat, aiTextureType type,string typeName);

};

#endif // BASICMODEL_H
