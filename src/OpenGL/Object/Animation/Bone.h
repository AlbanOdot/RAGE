#ifndef BONE_H
#define BONE_H
#include <vector>
#include "./src/OpenGL/Object/Model/model.h"

class Bone : public Model
{
public:
  Bone(glm::vec3 origin = glm::vec3(-1.0,0.0,0.0), glm::vec3 direction = glm::vec3(1.0,0.0,0.0), float length = 2.0f, float radius = 0.3f);
  virtual void draw() const;

  /* Hierarchy functions */
  Bone addChild(glm::vec3 direction = glm::vec3(1.0,0.0,0.0), float length = 2.0f, float radius = 0.3f);
  void addChild(Bone& child);

  void addParent(const Bone& parent);

  void setRoot(bool root);
  bool isRoot() const { return m_root;}

  /* Hierarchy  action functions */
  void rotate(float theta, glm::vec3 axis);
  //void rotate(Quaternion q);
  void stretch(glm::vec3 direction, float length);

  /* Action functions */
  void rotate(const glm::mat4& R);
  void rotateLocal(float theta, glm::vec3 axis);
  //void rotateLocal(Quaternion q);

protected:
  static unsigned int m_bone_count;
  unsigned int m_id;
  /*  Hierarchy    */
  vector<Bone> m_parents;
  vector<Bone> m_children;
  bool m_root;

  /* Bone data */
  glm::vec3 m_origin;
  glm::vec3 m_direction;
  float m_length;
  float m_radius;
};

typedef Bone Skeletton;
#endif // BONE_H
