#ifndef RAYCAST_H
#define RAYCAST_H
#include "./src/OpenGL/Object/Model/Mesh.h"
#include "./src/OpenGL/Object/Model/AABB.h"
#include "./src/Math/ray.h"

namespace Math {
  namespace  RayCast{

    /* Compute the instersection between a ray and the AABB of an object */
    inline bool vsAABB(const Ray& r, const AABB& aabb);
    /* Compute the intersection between a ray and a triangle */
    inline bool vsTriangle(const Ray& r, const glm::vec3& a, const glm::vec3& b, const glm::vec3& c);
    /* Compute the intersection between a ray and a triangle and store it in intersectionPosition*/
    inline bool vsTriangle(const Ray& r, const glm::vec3& a, const glm::vec3& b,const glm::vec3& c, glm::vec3& intersectionPosition);
    /* Compute the intersection between a ray and a mesh */
    inline bool vsMesh( const Mesh& mesh);
    /* Compute the intersection between a ray and a plane */
    inline bool vsPlane(const Ray& r, const glm::vec3 a, const glm::vec3& normal, glm::vec3& res);
    /* Compute the intersection between a ray and a cylinder */
    inline bool vsCylinder(const Ray& r, const glm::vec3& a, glm::vec3& b, float radius);
  };
};

#include "RayCast.inl"

#endif // RAYCAST_H
