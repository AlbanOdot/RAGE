#include "AnimatedModel.h"
#include <iostream>
#include "../../opengl_stuff.h"
#include "./src/Math/distance.h"
#include "./src/Math/Algorithm.h"
#include "./src/Math/utils.h"
#include "./src/Math/DualQuaternion.h"
#include "./src/Math/Quaternion.h"
#include <omp.h>
AnimatedModel::AnimatedModel()
{

}

AnimatedModel::AnimatedModel(const Mesh& m){
  m_meshes.emplace_back(m);
}
AnimatedModel::AnimatedModel(const Mesh& m, const int metrique){
  m_metrique = metrique;
  m_meshes.emplace_back(m);
}

void AnimatedModel::loadModel(string path){
  Assimp::Importer import;
  const aiScene *scene = import.ReadFile(path, aiProcess_Triangulate |aiProcess_GenUVCoords
                                         |aiProcess_FlipUVs | aiProcess_GenNormals);
  cout << "*Loading of : "<< getFileName(path)<<endl;
  if(!scene || scene->mFlags & AI_SCENE_FLAGS_INCOMPLETE || !scene->mRootNode)
    {
      cout << "ERROR::ASSIMP::" << import.GetErrorString() << endl;
      return;
    }
  m_directory = path.substr(0, path.find_last_of('/'));

  processNode(scene->mRootNode, scene);
  m_draw_aabb = true;

  /*for(const auto& mesh : m_meshes)
    m_aabb.computeAABB(&mesh);*/

}

void AnimatedModel::processNode(aiNode *node, const aiScene *scene){
  // process all the node's meshes (if any)
  for(unsigned int i = 0; i < node->mNumMeshes; ++i)
    {
      aiMesh *mesh = scene->mMeshes[node->mMeshes[i]];
      m_meshes.push_back(processMesh(mesh));
    }
  // then do the same for each of its children
  for(unsigned int i = 0; i < node->mNumChildren; ++i)
    {
      processNode(node->mChildren[i], scene);
    }
}

AnimatedMesh AnimatedModel::processMesh(aiMesh *mesh){
  vector<unsigned int> indices;
  vector<float> vertices;
  vector<float> normals;
  vector<float> colors;
  vector<float> uv;
  for(  unsigned int i = 0; i < mesh->mNumVertices; ++i){

      vertices.push_back(mesh->mVertices[i].x);
      vertices.push_back(mesh->mVertices[i].y);
      vertices.push_back(mesh->mVertices[i].z);

      normals.push_back(mesh->mNormals[i].x);
      normals.push_back(mesh->mNormals[i].y);
      normals.push_back(mesh->mNormals[i].z);
      if (mesh->HasTextureCoords(i)){
          uv.push_back(mesh->mTextureCoords[0][i].x);
          uv.push_back(mesh->mTextureCoords[0][i].y);
        }else{
          uv.push_back(0.0);
          uv.push_back(0.0);
        }
      if(mesh->HasVertexColors(i)){
          colors.push_back(mesh->mColors[0][i].r);
          colors.push_back(mesh->mColors[0][i].g);
          colors.push_back(mesh->mColors[0][i].b);
        }else{
          colors.push_back(0.43f);
          colors.push_back(0.43f);
          colors.push_back(0.43f);
        }
    }
  for(unsigned int i = 0; i < mesh->mNumFaces; ++i)
    {
      aiFace face = mesh->mFaces[i];
      for(unsigned int j = 0; j < face.mNumIndices; ++j)
        indices.push_back(face.mIndices[j]);
    }
  return AnimatedMesh(vertices,normals,uv,colors,indices);
}

void AnimatedModel::draw() const{

  for(const auto& mesh : m_meshes ){
      mesh.draw();
    }
  if( m_draw_aabb ){
      glLineWidth(2.0f);
      m_aabb.draw();
    }

}

void AnimatedModel::translate(const glm::vec3& vec){
  m_model = glm::translate(m_model,vec);
  m_skeletton.translate(vec);
}

void AnimatedModel::translate(const float x, const float y, const float z){
  glm::vec3 vec(x,y,z);
  m_model = glm::translate(m_model,vec);
  m_skeletton.translate(vec);
}

void AnimatedModel::translate(const glm::mat4& T){
  m_model = T;
  m_skeletton.translate(T);
}

void AnimatedModel::translateQuat(const glm::vec3& t){
  m_quat.translate(t);
  m_skeletton.translateQuat(t);
}


void AnimatedModel::rotate(const float angle, const glm::vec3& vec){
  m_model = glm::rotate(m_model, glm::radians(angle), vec);
  m_skeletton.rotate(m_model);
}

void AnimatedModel::rotate(const glm::mat4& R){
  m_model = R;
  m_skeletton.rotate(m_model);
}

void AnimatedModel::rotate(const float angle, const float x, const float y, const float z){
  m_model = glm::rotate(m_model, glm::radians(angle), glm::vec3(x,y,z));
  m_skeletton.rotate(m_model);
}

void AnimatedModel::rotate(const Math::DualQuaternion& q){
  m_quat = Math::DualQuaternion(q);
  m_skeletton.rotate(q);
}

void AnimatedModel::stretch(const float length, const glm::vec3& direction){
  glm::vec3 stretch = length * direction;
  m_model[0][0] = stretch.x;
  m_model[1][1] = stretch.y;
  m_model[2][2] = stretch.z;
}

void AnimatedModel::stretch(const float x, const float y, const float z){
  m_model[0][0] = x;
  m_model[1][1] = y;
  m_model[2][2] = z;
}


void AnimatedModel::computeWeights(){
  vector<Bone *> boneList = m_skeletton.boneList();
  unsigned int nbBones = boneList.size();
  glm::vec4 weightv4;
  glm::vec4 weightv4Idx;
  for( auto& mesh : m_meshes){
      mesh.resetWeight();
      mesh.m_weights.resize(4*mesh.m_vertices.size());
      mesh.m_weight_indices.resize(4*mesh.m_vertices.size());
#pragma omp for
      for( unsigned int i = 0; i < (mesh.m_vertices.size() / 3); ++i){
          //cout << " Il y a "<<omp_get_num_threads()<<"fils"<<endl;
          glm::vec3 vertex(mesh.m_vertices[3*i],mesh.m_vertices[3*i+1],mesh.m_vertices[3*i+2]);
          vector<float> weights;
          float totalWeight = 0.f;
          //Compute weights
          for(const auto& bone  : boneList){
              float w = 0.f;
              float d = 0.f;
              switch(m_metrique){
                case 0:
                  d = Math::Distance::segmentEuclid(bone->origin(), bone->origin() + bone->length() * bone->direction(),vertex);
                  w = d > m_max_dist ? 1.f/(35.f * d) : d != 0.f ? 1.f/d : 1.f;
                  break;
                case 1:
                  float d = Math::Distance::segmentRadial(bone->origin(), bone->origin() + bone->length() * bone->direction(),vertex,m_max_dist,4);
                  w = d != 0.f ? 1.f / d : 1.f;
                  break;
                }
              //Si le point est sur l'os alors il bouge comme l'os
              weights.emplace_back(w);
            }
          //Fill with 0 if less than 4 bones
          for( unsigned int i = 0; i < 4 - nbBones; ++i){
              weights.emplace_back(0.f);
            }
          //Find the 4 most important bone and normalize the weights
          Math::Algorithm::find4MaxValues(weights,weightv4,weightv4Idx);
          totalWeight = weightv4.x + weightv4.y + weightv4.z + weightv4.w;
          if(totalWeight == 0.f){
              weightv4 = glm::vec4(1.f,1.f,1.f,1.f);
            }
          weightv4 = weightv4 / totalWeight;
          mesh.m_weights[4*i] = weightv4.x;mesh.m_weights[4*i+1] = weightv4.y;
          mesh.m_weights[4*i+2] = weightv4.z; mesh.m_weights[4*i+3] = weightv4.w;
          mesh.m_weight_indices[4*i] = weightv4Idx.x; mesh.m_weight_indices[4*i+1] = weightv4Idx.y;
          mesh.m_weight_indices[4*i+2] = weightv4Idx.z;  mesh.m_weight_indices[4*i+3] = weightv4Idx.w;
          //mesh.addWeights(weightv4,weightv4Idx);
        }//i < mesh.m_vertices.size() - 2
      mesh.setupMesh();
    }
}

void AnimatedModel::applyBonesTransformation(){
  vector<Bone *> boneList = m_skeletton.boneList();
  vector<float> new_vertex;
  vector<float> new_normal;
  vector<glm::mat4 > models = {glm::mat4(1.f)};
  //Le premier os est toujours l'os

  for(const auto& bone : boneList){
      models.push_back(bone->model());
    }
  for( auto& mesh : m_meshes){
      mesh.transformMesh(models);
    }

}

vector<glm::mat4> AnimatedModel::models(){
  vector<glm::mat4 > models = {glm::mat4(1.f)};
  vector<Bone *> boneList = m_skeletton.boneList();
  for(const auto& bone : boneList){
      models.push_back(bone->model());
    }

  while( models.size() < 20){
      models.emplace_back(glm::mat4(1.f));
    }
  return models;
}

vector<glm::vec4> AnimatedModel::quats(){
  //1 quat de rotation et un quat de translation par os
  vector<glm::vec4> dq = {glm::vec4(1,0,0,0),glm::vec4(0)};
  vector<Bone *> boneList = m_skeletton.boneList();
  for(const auto& bone : boneList){
      dq.push_back(bone->quaternion().q0().m_coef);
      dq.push_back(bone->quaternion().qe().m_coef);
    }
  while( dq.size() < 40){
      dq.push_back(glm::vec4(1,0,0,0));
      dq.push_back(glm::vec4(0));
    }
  return dq;
}

void AnimatedModel::tresholdUp(bool up){
  if(m_max_dist - 0.05f > m_min_dist){
      m_max_dist = up ? m_max_dist + 0.05f : m_max_dist - 0.05f;
    }else{
      m_max_dist = up ? m_max_dist + 0.05f : m_max_dist ;
    }
  cout << "Distance threshold is now : " << m_max_dist<<endl;
  computeWeights();
}

void AnimatedModel::applyBonesTransformationQuat(){
  vector<Bone *> boneList = m_skeletton.boneList();
  vector<float> new_vertex;
  vector<float> new_normal;
  vector<Math::DualQuaternion > quats = {Math::DualQuaternion::identity()};
  //Le premier os est toujours l'os

  for(const auto& bone : boneList){
      quats.push_back(bone->quaternion());
    }
  for( auto& mesh : m_meshes){
      mesh.transformMesh(quats);
    }
}
