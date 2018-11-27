#ifndef MODEL_H
#define MODEL_H
#include "mesh.h"
#include <string>
#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>
#include <glm/mat4x4.hpp>

class Model
{
public:
    /*  Functions   */
    Model(string path)
    {
        loadModel(path);
    }
    void draw() const;
    vector<Mesh> m_meshes;
    glm::mat4 m_model;
private:
    /*  Model Data  */

    string m_directory;
    /*  Functions   */
    void loadModel(const string path);
    void processNode(aiNode *node, const aiScene *scene);
    Mesh processMesh(aiMesh *mesh);
    //vector<Texture> loadMaterialTextures(aiMaterial *mat, aiTextureType type,string typeName);

};

#endif // MODEL_H
