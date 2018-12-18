#ifndef ANIMATEDMESH_H
#define ANIMATEDMESH_H

#include "./src/OpenGL/Object/Model/mesh.h"
#include "./Bone.h"

class AnimatedMesh : public Mesh
{
public:

  vector<float> m_weights;
  vector<float> m_weight_indices;
  bool m_is_complete;

  AnimatedMesh(const vector<float> vertices, const vector<float> normals, const vector<float> UV,
               const vector<float> colors,   const  vector<unsigned int>  indices);
  AnimatedMesh();
  AnimatedMesh(const Mesh& m);
  void attachWeights(const vector<float> weights, const vector<float> weight_indices);
  void transformMesh(const vector<glm::mat4>& transfo);
  void transformMesh(const vector<Math::DualQuaternion>& quats);
  void addWeights(const glm::vec4& w, const glm::vec4& widx) {   Point4(w);WeightIdx(widx);}
  //void draw() const;
  void setupMesh();
  void setupMesh( const vector<float> vertice, const vector<float> normals);
  void resetWeight() { m_weight_indices.clear(); m_weights.clear();}
protected:
  unsigned int m_WBO, m_WIBO;

  inline void WeightIdx(unsigned int a,unsigned int b, unsigned int c, unsigned int d)
  { m_weight_indices.push_back(a); m_weight_indices.push_back(b); m_weight_indices.push_back(c);m_weight_indices.push_back(d);}
  inline void Point4(float a, float b, float c, float d)
  { m_weights.push_back(a); m_weights.push_back(b); m_weights.push_back(c);m_weights.push_back(d);}
  inline void WeightIdx(const glm::vec4& t)
  { m_weight_indices.push_back(t.x); m_weight_indices.push_back(t.y); m_weight_indices.push_back(t.z);m_weight_indices.push_back(t.w);}
  inline void Point4(const glm::vec4& t)
  { m_weights.push_back(t.x); m_weights.push_back(t.y); m_weights.push_back(t.z);m_weights.push_back(t.w);}

};

#endif // ANIMATEDMESH_H
