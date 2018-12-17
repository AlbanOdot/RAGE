#include "AnimatedModel.h"
#include <iostream>
#include "../../opengl_stuff.h"
#include "./src/Math/distance.h"
#include "./src/Math/Algorithm.h"
#include "./src/Math/utils.h"

AnimatedModel::AnimatedModel()
{

}

AnimatedModel::AnimatedModel(const Mesh& m){
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
/*
void AnimatedModel::translate(const Quaternion& q){
  m_model =
}
*/

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

/*
void AnimatedModel::rotate(const Quaternion& q){
  m_model =
}*/

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
      for( unsigned int i = 0; i < mesh.m_vertices.size() - 2; i+= 3){
          glm::vec3 vertex(mesh.m_vertices[i],mesh.m_vertices[i+1],mesh.m_vertices[i+2]);
          vector<float> weights;
          float totalWeight = 0.f;
          //Compute weights

          for(const auto& bone  : boneList){
              float d = Math::Distance::segmentEuclid(bone->origin(), bone->origin() + bone->length() * bone->direction(),vertex);
              //Si le point est sur l'os alors il bouge comme l'os
              if(d <= EPSILON){
                  for( unsigned long p = 0; p < weights.size(); weights[p++] = 0.f){}//On reset tous les poids
                  weights.push_back(1.f);
                  break;
                }
              if( d > m_max_dist){
                  weights.push_back(0.f);
                }else{
                  weights.emplace_back(1.f / d);
                }
            }
          //Fill with 0 if less than 4 bones
          for( unsigned int i = 0; i < 4 - nbBones; ++i){
              weights.emplace_back(0.f);
            }
          Math::Algorithm::find4MaxValues(weights,weightv4,weightv4Idx);
          totalWeight = weightv4.x + weightv4.y + weightv4.z + weightv4.w;
          weightv4 = weightv4 / totalWeight;
          mesh.addWeights(weightv4,weightv4Idx);
        }//i < mesh.m_vertices.size() - 2
      mesh.setupMesh();
    }
}

void AnimatedModel::applyBonesTransformation(const glm::vec3& rotOrig){
  vector<Bone *> boneList = m_skeletton.boneList();
  vector<float> new_vertex;
  vector<float> new_normal;
  vector<glm::mat4 > models = {glm::mat4(1.f)};
  vector<glm::mat4> invRestPose ={glm::mat4(1.f)};
  //Le premier os est toujours l'os

  for(const auto& bone : boneList){
      models.push_back(bone->model());
      invRestPose.push_back(glm::inverse(bone->restPose()));
    }
  for( auto& mesh : m_meshes){
      mesh.transformMesh(models,invRestPose);
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

void AnimatedModel::tresholdUp(bool up){
  if(m_max_dist - 0.05f> 0.5f){
      m_max_dist = up ? m_max_dist + 0.05f : m_max_dist - 0.05f;
    }else{
      m_max_dist = up ? m_max_dist + 0.05f : m_max_dist ;
    }
  computeWeights();
}

