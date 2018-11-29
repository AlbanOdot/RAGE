#ifndef SHAPE_H
#define SHAPE_H
#include "../Model/mesh.h"

class Shape : public Mesh
{
public:
  typedef enum {SPHERE,CYLINDER,TETRAHEDRON,ICOSAHEDRON, CRISTAL} SHAPE;

  Shape(vector<float> vertices, vector<float> normals, vector<float> UV, vector<float> colors, vector<unsigned int> indices, SHAPE shape):
    Mesh(vertices, normals, UV, colors, indices), m_shape(shape){}

  Shape(SHAPE shape) : Mesh(), m_shape(shape){}

  SHAPE type() const { return m_shape;}

protected:
  SHAPE m_shape;

};

#endif // SHAPE_H
