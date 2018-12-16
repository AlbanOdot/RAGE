#ifndef UTILS_H
#define UTILS_H
#include "glm.hpp"
#define GLM_ENABLE_EXPERIMENTAL
#include <glm/gtx/transform.hpp>
#include <glm/gtx/vector_angle.hpp>

#include <iostream>

namespace  Math{

  namespace Utils{

    inline void displayMatrix(const glm::mat4& mat){
      std::cout << "("<<mat[0][0]<<" "<<mat[0][1]<<" "<<mat[0][2]<<" "<<mat[0][3]<<")"<<std::endl;
      std::cout << "("<<mat[1][0]<<" "<<mat[1][1]<<" "<<mat[1][2]<<" "<<mat[1][3]<<")"<<std::endl;
      std::cout << "("<<mat[2][0]<<" "<<mat[2][1]<<" "<<mat[2][2]<<" "<<mat[2][3]<<")"<<std::endl;
      std::cout << "("<<mat[3][0]<<" "<<mat[3][1]<<" "<<mat[3][2]<<" "<<mat[3][3]<<")"<<std::endl;
    }

    inline void displayVec3(const glm::vec3& v){
      std::cout << "("<<v[0]<<" "<<v[1]<<" "<<v[2]<<")"<<std::endl;
    }
    inline void displayVec4(const glm::vec4& v){
      std::cout << "("<<v[0]<<" "<<v[1]<<" "<<v[2]<<" "<<v[3]<<")"<<std::endl;
    }



  }
}

#endif // UTILS_H
