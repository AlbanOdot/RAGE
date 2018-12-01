#include "model.h"
#include <iostream>
#include "../../opengl_stuff.h"

void Model::draw() const{
  for(const auto& mesh : m_meshes ){
      mesh.draw();
    }

  if( m_draw_aabb ){
      glLineWidth(2.0f);
      m_aabb.draw();
    }

}

string getFileName(const string& s) {

  char sep = '/';

#ifdef _WIN32
  sep = '\\';
#endif

  size_t i = s.rfind(sep, s.length());
  if (i != string::npos) {
      return(s.substr(i+1, s.length() - i));
    }

  return("");
}

void Model::loadModel(string path){
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
  m_aabb.computeAABB(m_meshes);

}

void Model::processNode(aiNode *node, const aiScene *scene){
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
Mesh Model::processMesh(aiMesh *mesh){
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
  return Mesh(vertices,normals,uv,colors,indices);
}

//Generate a sphere
Model::Model(float radius,glm::vec3 center){
  m_meshes.push_back(Sphere(center, radius));
}
//Generate generic shape
Model::Model(Shape::SHAPE s,glm::vec3 origin , glm::vec3 direction, float length, float radius){
  //TODO IMPLEMENTER CA
  switch(s){
    case Shape::SHAPE::TETRAHEDRON:
      m_meshes.push_back(Tetrahedron(origin,direction,length,radius));
    break;
    default:
      loadModel("../DataFiles/CylinderAnim.obj");
      break;
    }
}

void Model::translate(glm::vec3 vec){
    m_model = glm::translate(m_model,vec);
}

void Model::translate(float x, float y, float z){
    m_model = glm::translate(m_model,glm::vec3(x,y,z));
}

void Model::rotate(float angle, glm::vec3 vec){
    m_model = glm::rotate(m_model, glm::radians(angle), vec);
}

void Model::rotate(const glm::mat4& R){
  m_model = R;
}
void Model::stretch(glm::vec3 direction, float length){
  glm::vec3 stretch = length * direction;
  m_model[0][0] = stretch.x;
  m_model[1][1] = stretch.y;
  m_model[2][2] = stretch.z;
}

