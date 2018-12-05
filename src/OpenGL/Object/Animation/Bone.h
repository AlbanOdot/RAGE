#ifndef BONE_H
#define BONE_H
#include <vector>
#include <deque>
#include "./src/OpenGL/Object/Model/Model.h"
#include "./src/Math/RayCast.h"

class Bone : public Model
{
public:
  /* CONSTRUCTORs */
  Bone(glm::vec3 origin = glm::vec3(-1.0,0.0,0.0), glm::vec3 direction = glm::vec3(1.0,0.0,0.0), float length = 2.0f, float radius = 0.3f, bool root = true);
  void            computeBone(glm::vec3 origin = glm::vec3(-1.0,0.0,0.0), glm::vec3 direction = glm::vec3(1.0,0.0,0.0), float length = 2.0f, float radius = 0.3f, bool root = true);
  /* Hierarchy functions */
  Bone            addChild(glm::vec3 direction = glm::vec3(1.0,0.0,0.0), float length = 2.0f, float radius = 0.3f);
  Bone            addChild(deque<int> path,glm::vec3 direction, float length, float radius);
  void            addChild(Bone& child);
  virtual Bone*   clickOnSkeletton(Ray& r);
  void            addParent(const Bone& parent);

  /* Acessors */
  bool            isRoot() const { return m_root;}
  void            setRoot(bool root);
  glm::vec3       origin() const { return m_origin;}
  glm::vec3       direction() const { return m_direction;}
  float           length() const { return m_length;}
  float           radius() const { return m_radius;}
  vector<Bone>&   children() { return m_children;}//BECAREFULL WITH THIS THIS FUNCTION
  Bone*           child(int i) { if(m_children.size() > i && i >= 0) return &(m_children[i]); return nullptr;}
  vector<int>     parentPath() { return m_parent->m_path; }
  vector< Bone *> boneList() ;
  void            pushChild( vector< Bone *>& list);

  /* ROTATION AND MODEL CHANGE STUF */
  virtual void translate(const glm::vec3& vec) override;
  virtual void translate(const float x, const float y, const float z) override;
  virtual void translate(const glm::mat4& T) override;
  //virtual void translate(const Quaternion& q);

  virtual void rotate(const float angle, const glm::vec3& vec) override;
  virtual void rotate(const glm::mat4 R) override;
  virtual void rotate(const float angle, float x, float y, float z) override;
  //virtual void rotate(const Quaternion& q);

  virtual void stretch(const float length, const glm::vec3& direction = glm::vec3(1,1,1)) override;
  virtual void stretch(const float x, float y, float z) override;
  //On peut faire ca avec des quaternions ?

  /* Draw related stuff */
  virtual void draw() const override;
  virtual void displayAABB(const bool d) override;
  unsigned int ID() const { return m_id;}
protected:
  static unsigned int m_bone_count;
  unsigned int        m_id;
  vector<int>         m_path;
  /*  Hierarchy    */
  Bone*               m_parent;
  vector<Bone>        m_children;
  bool                m_root;

  /* Bone data */
  glm::vec3           m_origin;
  glm::vec3           m_direction;
  float               m_length;
  float               m_radius;
};

typedef Bone Skeletton;
#endif // BONE_H
