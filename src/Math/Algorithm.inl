#include "Algorithm.h"
#include <algorithm>
#include <functional>
#include <queue>

/*
 * Trouve une base orthonomée à partir du vecteur v1
 *
 * Modifie les vecteurs u1 et u2
 */
void Math::Algorithm::GramSchmidt(const glm::vec3& u1, glm::vec3& u2, glm::vec3& u3){
  u2 = u2 - projection(u1,u2);
  u2 = glm::normalize(u2);
  u3 = u3 - projection(u1,u3) - projection(u2,u3);
  u3 = glm::normalize(u3);
}

/*
 * project v onto u
 * projection(v,u) = v * (dot(u,v) / dot(v,v))
 *
 */
glm::vec3 Math::Algorithm::projection(const glm::vec3& v, const glm::vec3& u){
  return v * (glm::dot(u,v) / glm::dot(v,v));

}

void Math::Algorithm::find4MaxValues(const std::vector<float>& findIn, glm::vec4& foundOut, glm::vec4& foundOutIdx){
  std::priority_queue< std::pair<float, int>, std::vector< std::pair<float, int> >, std::greater <std::pair<float, int> > > q;
  for (unsigned long i = 0; i < findIn.size(); ++i) {
      if(q.size()<4)
        q.push(std::pair<double, int>(findIn[i], i+1));
      else if(q.top().first < findIn[i]){
          q.pop();
          q.push(std::pair<double, int>(findIn[i], i+1));
        }
    }
  foundOut.w = q.top().first;
  foundOutIdx.w = foundOut.w != 0.f ? q.top().second: 0;
  q.pop();
  foundOut.z = q.top().first;
  foundOutIdx.z = foundOut.z != 0.f ? q.top().second: 0;
  q.pop();
  foundOut.y = q.top().first;
  foundOutIdx.y = foundOut.y != 0.f ? q.top().second: 0;
  q.pop();
  foundOut.x = q.top().first;
  foundOutIdx.x = foundOut.x != 0.f ? q.top().second: 0;
}
