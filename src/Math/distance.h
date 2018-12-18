#ifndef DISTANCE_H
#define DISTANCE_H
#include "glm.hpp"
#define GLM_ENABLE_EXPERIMENTAL
#include <glm/gtx/transform.hpp>
#include <glm/gtx/vector_angle.hpp>

#include <vector>
#include <cmath>

namespace  Math{

  namespace Distance{
    inline float min(const float a,const float b){
      return a < b ? a : b;
    }

    inline float max(const float a, const float b){
      return a > b ? a : b;
    }

    inline float euclid(const glm::vec3& p1, const glm::vec3& p2, unsigned int power = 2){
      if( power == 2)
        return glm::dot(p1-p2,p1-p2);
      return std::pow(glm::length(p1-p2),power);
    }

    inline float manhattan(const glm::vec3& p1, const glm::vec3& p2, unsigned int power = 1){
      return std::pow(abs(p1.x-p2.x) + abs(p1.y-p2.y) + abs(p1.z-p2.z),power);
    }

    inline float radialClosed(const glm::vec3& p1, const glm::vec3& p2, const float R, unsigned int power = 2){
      float R2 = R*R;
      float L2 = glm::length2(p1-p2);
      if(power == 2){
          float w = (R2-L2)/R2;
          return w >0.f ? w : 0.f;
        }
      if(power == 4){
          float R4 = R2*R2;
          float w =1.f - L2/R2 + (L2*L2)/R4;
          return w > 0.f ? w : 0;
        }
      float w = (1.f/std::pow(R,power)) * std::pow(R2 - L2,power/2);
      return w > 0.f ? w : 0.f;
    }

    //Distance(P,AB)
    inline float segmentEuclid(const glm::vec3& A, const glm::vec3& B, const glm::vec3& C, unsigned int power = 1){
      glm::vec3 AB = B-A;
      float r = glm::dot(C-A,AB) / glm::dot(AB,AB);
      r = min(max(r,0.f),1.f);
      return euclid(C,A + AB * r,power);
    }

    inline float segmentRadial(const glm::vec3& A, const glm::vec3& B, const glm::vec3& C, const float R, unsigned int power = 1){
      glm::vec3 AB = B-A;
      float r = glm::dot(C-A,AB) / glm::dot(AB,AB);
      r = min(max(r,0.f),1.f);
      return radialClosed(C,A + AB * r,R,power);
    }

  }
}

#endif // DISTANCE_H
