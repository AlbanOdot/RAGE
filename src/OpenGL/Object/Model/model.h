#ifndef MODEL_H
#define MODEL_H
#include "mesh.h"
#include <string>
#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>
#include <glm/mat4x4.hpp>
#include "src/OpenGL/Object/Shapes/Shape.h"
#include "src/OpenGL/Object/Shapes/Sphere.h"
#include "src/OpenGL/Object/Shapes/Tetrahedron.h"
#include "src/OpenGL/Object/Shapes/Cristal.h"
class Model
{
public:
   virtual ~Model(){}
    /*  Functions   */
    //Generate a sphere
    Model(unsigned char c){/*ONLY CALL FROM INHERITANCE*/}
    Model(float radius,glm::vec3 center = glm::vec3(0.,0.,0.));
    //Generate generic shape
    Model(Shape::SHAPE s,glm::vec3 origin = glm::vec3(-1.0,0.0,0.0), glm::vec3 direction = glm::vec3(1.0,0.0,0.0), float length = 2.0, float radius = 0.5);
    Model(string path)
    {
        loadModel(path);
    }
    virtual void draw() const;
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
