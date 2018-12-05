#include "Cylinder.h"

Cylinder::Cylinder(glm::vec3 origin, glm::vec3 direction, float length, float radius)
  : Shape(CYLINDER), m_origin(origin), m_direction(direction), m_length(length), m_radius(radius)
{
  int nFaces=32;
  int ech = 32;
  glm::vec3 xPlane(1,0,0);
  glm::vec3 yPlane(0,0,1);


  const float thetaInc( (float)M_PI*2.f / nFaces );
  for ( int i = 0; i <= nFaces; ++i )
    {
      float theta = i * thetaInc;

      for(int j=0; j<ech; j++){
          glm::vec3 p = glm::vec3(j/(float)ech) * (origin + direction);
          Point3(p + radius * (std::cos( theta ) * xPlane + std::sin( theta ) * yPlane ));
        }

      for( int j =0; j<ech  ; ++j){

          Normal(glm::vec3(std::cos(theta), 0, std::sin(theta)));
          Colors(glm::vec3(std::cos(theta), 0, std::sin(theta)));
        }

      theta = i*thetaInc;

      for(unsigned int v=0;v<ech;++v){
          const float phi = v  * M_PI / (ech-1);
          Point2(0.5f * theta / M_PI, phi / (float)M_PI);
        }
    }

  for ( int i = 0; i < nFaces ; ++i){
      for ( int j = 0; j < ech-1; ++j )
        {
          // Outer face.
          unsigned int o1 = i * ech + j;
          unsigned int o2 = (i+1) * ech + j;
          unsigned int o3 = o1 + 1;
          unsigned int o4 = o2 + 1;

          Triangle( o1, o2, o3 );
          Triangle( o2, o4, o3 );
        }
    }

  setupMesh();

}
