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
#define SQRT2 1.414213562373095048801688724209698
#define SQRT1_2  0.7071067811865475255008
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
      static float R2 = R*R;
      return (1.f/std::pow(R,power)) * std::pow((R2 - glm::length2(p1-p2)),power/2);
    }

    //Distance(P,AB)
    inline float segmentEuclid(const glm::vec3& A, const glm::vec3& B, const glm::vec3& C, unsigned int power = 1){
      glm::vec3 AB = B-A;
      float r = glm::dot(C-A,AB) / glm::dot(AB,AB);
      r = min(max(r,0.f),1.f);
      //cout << "On a R = "<<r<<endl;
      return euclid(C,A + AB * r,power);
    }

  }
}

#endif // DISTANCE_H
