#include "Sphere.h"

Sphere::Sphere(glm::vec3 center, float radius) : Shape(SPHERE), m_center(center), m_radius(radius)
{
  unsigned int slices=20, stacks=20;

  for ( unsigned int u = 0; u <= slices; ++u )
    {
      float phi = 2 * u * M_PI / slices;
      for ( unsigned int v = 0; v <= stacks; ++v )
        {
          // Regular vertices on the sphere.
          float theta = v * M_PI / stacks ;
          float a = -std::cos( phi ) * std::sin( theta );
          float b = std::cos( theta );
          float c = std::sin( phi ) * std::sin( theta );
          Normal( a,b,c);
          Colors(a,b,c);
          Point3(radius * a + center.x,radius * b + center.y,radius * c + center.z);
          Point2((float)u/slices,(float)v/stacks);

          // Regular triangles
          if ( v < stacks && u<slices)
            {
              const unsigned int nextSlice = ((u + 1) % (slices + 1)) * (stacks + 1);
              const unsigned int baseSlice = u * (stacks + 1);
              Triangle( baseSlice + v , baseSlice + v +1, nextSlice + v +1 );
              Triangle( baseSlice + v , nextSlice + v + 1, nextSlice + v  );
            }
        }
    }

  setupMesh();
}

