#ifndef ANIMATEDMODEL_H
#define ANIMATEDMODEL_H
#include "../Model/Model.h"
#include "AnimatedMesh.h"

class AnimatedModel : public Model
{
public:
  AnimatedModel();
  //Load a mesh from a file
  AnimatedModel(string path){loadModel(path);}

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
  vector<AnimatedMesh> meshes() const {return m_meshes;}
  vector<AnimatedMesh>& meshes()      { return m_meshes;}
  void meshes(const AnimatedMesh m)   { m_meshes.push_back(m);for(const auto& mesh : m_meshes) m_aabb.computeAABB(&mesh);}

  /* Skeletton related stuff */
  void computeWeights();
  void attachSkeletton(const Skeletton& skeletton) { m_skeletton = skeletton; computeWeights();}
  void applyBonesTransformation();
  Skeletton& skeletton() { return m_skeletton;}

protected:
  vector<AnimatedMesh> m_meshes;
  Skeletton m_skeletton;

private:
  /*  Functions   */
  void loadModel(const string path);
  void processNode(aiNode *node, const aiScene *scene);
  AnimatedMesh processMesh(aiMesh *mesh);
  //vector<Texture> loadMaterialTextures(aiMaterial *mat, aiTextureType type,string typeName);
};

#endif // ANIMATEDMODEL_H
