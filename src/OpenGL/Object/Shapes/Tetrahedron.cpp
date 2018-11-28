#include "Tetrahedron.h"

Tetrahedron::Tetrahedron(glm::vec3 origin, glm::vec3 direction, float length, float radius)
  : Shape(TETRAHEDRON), m_origin(origin), m_direction(direction), m_length(length), m_radius(radius)
{

}
