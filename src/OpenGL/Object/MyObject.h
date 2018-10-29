#ifndef MYOBJECT_H
#define MYOBJECT_H
//#include <OpenMesh/Core/IO/MeshIO.hh>
//#include <OpenMesh/Core/Mesh/TriMesh_ArrayKernelT.hh>
//#include <OpenMesh/Tools/Subdivider/Uniform/Composite/CompositeTraits.hh>
//#define TINYOBJLOADER_IMPLEMENTATION
#include "tiny_obj_loader.h"
#include "./opengl_stuff.h"

using namespace tinyobj;

class MyObject {

public:
    MyObject();
    ~MyObject();

    //Mesh from a file
    MyObject(const std::string& path);
    //Display
    virtual void draw();
    //Mesh actions
    //Return the new face count
    virtual unsigned int subdivideLoop();
    //Return the Error
    virtual float halfEdgeCollapse(const unsigned int faceCountTarget);
    //Return the Error
    virtual float EdgeCollapse( const unsigned int faceCountTarget);

    //Mesh info
    //if -1 return the sum over the whole mesh, if != -1 return the value of the asked patch
    inline unsigned int faceCount(int i = -1)     {int s =0;
                                                    if(i != -1 )
                                                        s = shapes_m[i].mesh.num_face_vertices.size();
                                                    else
                                                        for( unsigned long k = 0; k < shapes_m.size(); ++k)
                                                            s +=shapes_m[k].mesh.num_face_vertices.size();
                                                   return s;
                                                  }

    inline unsigned int verticesCount(int i = -1) {return 3 * faceCount( i );}
    inline unsigned int edgeCount(int i = -1)     {return 3 * faceCount( i );}
    inline unsigned int normalsCount(int i = -1)  {return 3 * faceCount( i );}
    inline unsigned int indicesCount(int i = -1)  {return 3 * faceCount( i );}
    GLuint getVAO() { return vao;}
    GLuint getVBO() { return vbo;}
    GLuint getNBO() { return nbo;}
    GLuint getEBO() { return ebo;}
protected:



    GLuint nbIndices = 0;
    GLuint vao = 0;//vertex array buffer
    GLuint vbo = 0;//vertices
    GLuint nbo = 0 ;//normals
    GLuint uvo = 0;//uv mapping
    GLuint cro = 0;//color
    GLuint ebo = 0;//topology

    //The actual mesh
    //Explications at the end of the file
    attrib_t attrib_m;
    std::vector<shape_t> shapes_m;
    std::vector<material_t> materials_m;

private:
    //Create/init all of the openGL attributes
    void loadGL();
};

#endif

/**
                    EXPLICATIONS

 * attrib contient la liste de tous les points, normales, coordonnées de textures et couleurs de l'objet
 * Un objet peut être constitué de plusieurs patch chacun représenté par un shape
 * Chacun de ces patch possède un matériau d'ou les vecteur de matériaux
 **/
