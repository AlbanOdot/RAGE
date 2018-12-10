#ifndef DISTANCE_H
#define DISTANCE_H
#include "glm.hpp"
#define GLM_ENABLE_EXPERIMENTAL
#include <glm/gtx/transform.hpp>
#include <glm/gtx/vector_angle.hpp>

#include <vector>

namespace  Math{

  namespace Distance{
#define SQRT2 1.414213562373095048801688724209698
#define SQRT1_2  0.7071067811865475255008
    inline float norm2(const glm::vec3& p1, const glm::vec3& p2, unsigned int power = 1){
      return std::powf(glm::length(p1-p2),power);
    }

    inline float manhattan(const glm::vec3& p1, const glm::vec3& p2, unsigned int power = 1){
      return std::powf(abs(p1.x-p2.x) + abs(p1.y-p2.y) + abs(p1.z-p2.z),power);
    }

    inline float radialClosed(const glm::vec3& p1, const glm::vec3& p2, const float R, unsigned int power = 2){
      static float R2 = R*R;
      return (1.f/std::pow(R,power)) * std::pow((R2 - glm::length2(p1-p2)),power/2);
    }

  };
};

#endif // DISTANCE_H
