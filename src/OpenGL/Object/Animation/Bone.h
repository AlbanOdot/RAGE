#ifndef BONE_H
#define BONE_H
#include <vector>
#include <deque>
#include "./src/OpenGL/Object/Model/model.h"
#include "./src/Math/RayCast.h"

class Bone : public Model
{
public:
  /* CONSTRUCTOR AND INTERACTION FUNCTIONS */
  Bone(glm::vec3 origin = glm::vec3(-1.0,0.0,0.0), glm::vec3 direction = glm::vec3(1.0,0.0,0.0), float length = 2.0f, float radius = 0.3f);
  virtual void draw() const;
  virtual void setAABB(bool d);
  virtual Bone* clickOnSkeletton(Ray& r);

  /* Hierarchy functions */
  Bone addChild(glm::vec3 direction = glm::vec3(1.0,0.0,0.0), float length = 2.0f, float radius = 0.3f);
  Bone addChild(deque<int> path,glm::vec3 direction = glm::vec3(1.0,0.0,0.0), float length = 2.0f, float radius = 0.3f);
  void addChild(Bone& child);
  void addParent(const Bone& parent);

  /* Acessors */
  bool isRoot() const { return m_root;}
  void setRoot(bool root);
  glm::vec3 origin() const { return m_origin;}
  glm::vec3 direction() const { return m_direction;}
  float length() const { return m_length;}
  float radius() const { return m_radius;}

  /* Action Function */
  void rotate(float theta, glm::vec3 axis) override;
  void rotate(const glm::mat4& R) override;
  //void stretch(glm::vec3 direction, float length) override;

  unsigned int ID() const { return m_id;}
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
