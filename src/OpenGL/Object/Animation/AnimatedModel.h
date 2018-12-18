#ifndef ANIMATEDMODEL_H
#define ANIMATEDMODEL_H
#include "../Model/model.h"
#include "AnimatedMesh.h"
#include "./src/OpenGL/Object/Shapes/shapes.h"
#include "./src/Math/DualQuaternion.h"

class AnimatedModel : public Model
{
public:
  AnimatedModel();
  //Load a mesh from a file
  AnimatedModel(const string& path){loadModel(path);}
  AnimatedModel(const Mesh& m);
  AnimatedModel(const Mesh& m, const int metrique);
  AnimatedModel(const string& path, const int metrique) : m_metrique(metrique){loadModel(path);}

  /* ROTATION AND MODEL CHANGE STUF */
  virtual void translate(const glm::vec3& vec);
  virtual void translate(const float x,const  float y,const  float z);
  virtual void translate(const glm::mat4& T);
  virtual void translateQuat(const glm::vec3& t);

  virtual void rotate(const float angle,const glm::vec3& vec);
  virtual void rotate(const float angle,const  float x,const  float y,const  float z);
  virtual void rotate(const glm::mat4& R);
  virtual void rotate(const Math::DualQuaternion& q);

  virtual void stretch(const float length, const glm::vec3& direction = glm::vec3(1,1,1));
  virtual void stretch(const float x,const  float y,const  float z);
  //On peut faire ca avec des quaternions ?

  /* Draw related stuff */
  virtual void draw() const;
  vector<AnimatedMesh> meshes() const {return m_meshes;}
  vector<AnimatedMesh>& meshes()      { return m_meshes;}
  void meshes(const AnimatedMesh m)   { m_meshes.push_back(m);for(const auto& mesh : m_meshes) m_aabb.computeAABB(&mesh);}
  vector<glm::mat4> models();
  vector<glm::vec4> quats();

  /* Skeletton related stuff */
  void computeWeights();
  void attachSkeletton(const Skeletton& skeletton) { m_skeletton = std::move(skeletton); computeWeights();}
  void applyBonesTransformation();
  void applyBonesTransformationQuat();
  Skeletton& skeletton() { return m_skeletton;}
  void displayAABB(bool t) { m_draw_aabb = t; m_skeletton.displayAABB(t);}
  void tresholdUp(bool up);
  void setMinDist(float m) { m_min_dist = m;}
  void setMaxDist(float M) { m_max_dist = M;}

protected:
  vector<AnimatedMesh> m_meshes;
  Skeletton m_skeletton;

private:
  float m_min_dist = 0.f;
  float m_max_dist = 0.5f;
  int m_metrique = 1;
  /*  Functions   */
  void loadModel(const string path);
  void processNode(aiNode *node, const aiScene *scene);
  AnimatedMesh processMesh(aiMesh *mesh);
  //vector<Texture> loadMaterialTextures(aiMaterial *mat, aiTextureType type,string typeName);
};

#endif // ANIMATEDMODEL_H
