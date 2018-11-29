#include "Bone.h"

Bone::Bone(glm::vec3 origin , glm::vec3 direction, float length , float radius )
  : Model((unsigned char)'c'), m_origin(origin), m_direction(direction), m_length(length), m_radius(radius)
{
  m_meshes.push_back(Cristal(origin,direction,length-radius/2,radius));
  float sRadius = 0.25 * radius;
  m_meshes.push_back(Sphere(origin + sRadius * direction,sRadius));
  m_meshes.push_back(Sphere(origin + (length + sRadius) * direction, sRadius ));
}
