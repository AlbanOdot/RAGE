#ifndef MODEL_H
#define MODEL_H

#include "../Shapes/Shapes.h"
#include "Model.h"

/*
 *
 *
 * This class is designed to represent randoms objects comming from an object file
 *
 *
 */
class ShapeModel :public Model
{
public:
  ShapeModel();
  //Generate generic shape from ../Shapes
  //Generate a sphere
  ShapeModel(float radius,glm::vec3 center = glm::vec3(0.,0.,0.));
  //Generate the shape specified by 1st arg
  ShapeModel(Shape::SHAPE s,glm::vec3 origin = glm::vec3(-1.0,0.0,0.0), glm::vec3 direction = glm::vec3(1.0,0.0,0.0), float length = 2.0, float radius = 0.5);

  /* Accessor */
  void addShape(const Shape& shape);
protected:
  //unsigned int m_shapes_count;
  unsigned int m_sphere_count;
  unsigned int m_cylinder_count;
  unsigned int m_tetrahedron_count;
  unsigned int m_icosahedron_count;
  unsigned int m_cristal_count;
  unsigned int m_cube_count;

};

#endif // MODEL_H
