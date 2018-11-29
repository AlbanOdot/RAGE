#ifndef MESH_H
#define MESH_H
#include <vector>

using namespace std;
class Mesh {
public:
  /*  Mesh Data  */
  vector<float> m_vertices;
  vector<float> m_normals;
  vector<float> m_uv;
  vector<float> m_colors;
  vector<unsigned int> m_indices;
  /*  Functions  */
  Mesh(vector<float> vertices, vector<float> normals, vector<float> UV, vector<float> colors, vector<unsigned int> indices);
  Mesh();
  void draw() const;
protected:
  /*  Render data  */
  unsigned int m_VAO, m_VBO, m_NBO, m_UVBO, m_CRBO, m_EBO;
  /*  Functions    */
  void setupMesh();

  inline void Triangle(unsigned int a,unsigned int b, unsigned int c) { m_indices.push_back(a); m_indices.push_back(b); m_indices.push_back(c);}
  inline void Point3(float a, float b, float c) { m_vertices.push_back(a); m_vertices.push_back(b); m_vertices.push_back(c);}
  inline void Colors(float a, float b, float c) { m_colors.push_back(a); m_colors.push_back(b); m_colors.push_back(c);}
  inline void Normal(float a, float b, float c) { m_normals.push_back(a); m_normals.push_back(b); m_normals.push_back(c);}
  inline void Point2(float a, float b) { m_uv.push_back(a); m_uv.push_back(b);}
};
#endif // MESH_H
