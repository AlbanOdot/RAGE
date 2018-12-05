#include "ShapeModel.h"

//Generate a sphere
ShapeModel::ShapeModel(float radius, glm::vec3 center) : Model(){
  addShape(Sphere(center, radius));
}

//Generate generic shape
ShapeModel::ShapeModel(Shape::SHAPE s,glm::vec3 origin , glm::vec3 direction, float length, float radius) : Model(){
  //TODO IMPLEMENTER CA
  switch(s){
    case Shape::SPHERE:
      addShape(Sphere(origin, radius));
      break;
    case Shape::CYLINDER:
      //TODO A pretty nice cylinder
      addShape(Cylinder(origin,direction,length,radius));
      break;
    case Shape::TETRAHEDRON:
      addShape(Tetrahedron(origin,direction,length,radius));
      break;
    case Shape::ICOSAHEDRON:
      //TODO A pretty nice icosahedron
      break;
    case Shape::CRISTAL:
      addShape(Cristal(origin,direction,length,radius));
      break;
    case Shape::CUBE:
      //It's dirty but in this case origin plays min's role and direction plays max's role
      addShape(Cube(origin,direction));
      break;
    default://Let this here in case i had new shapes and forget about this switch
      break;
    };
}



//SPHERE,CYLINDER,TETRAHEDRON,ICOSAHEDRON, CRISTAL, CUBE
void ShapeModel::addShape(const Shape& shape)
{
  m_meshes.push_back(shape);
  switch(shape.type()){
    case Shape::SPHERE:
      m_sphere_count++;
      break;
    case Shape::CYLINDER:
      m_cylinder_count++;
      break;
    case Shape::TETRAHEDRON:
      m_tetrahedron_count++;
      break;
    case Shape::ICOSAHEDRON:
      m_icosahedron_count++;
      break;
    case Shape::CRISTAL:
      m_cristal_count++;
      break;
    case Shape::CUBE:
      m_cube_count++;
      break;
    default://Same as above
      break;
    }
  //m_shapes_count++;
  m_aabb.computeAABB(m_meshes);
}
