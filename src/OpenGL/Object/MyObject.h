#ifndef MYOBJECT_H
#define MYOBJECT_H
#include <OpenMesh/Core/IO/MeshIO.hh>
#include <OpenMesh/Core/Mesh/TriMesh_ArrayKernelT.hh>
#include <OpenMesh/Tools/Subdivider/Uniform/Composite/CompositeTraits.hh>
#include <gl3.h>

typedef OpenMesh::TriMesh_ArrayKernelT<>  MyMesh;

class MyObject {

public:
    MyObject();
    ~MyObject();

    //Mesh from a file
    MyObject(const std::string& path);

    //Create/init all of the openGL attributes
    void loadGL();

    //Mesh actions
    //Return the new face count
    unsigned int subdivideLoop();
    //Return the Error
    float halfEdgeCollapse(const unsigned int faceCountTarget);
    //Return the Error
    float EdgeCollapse( const unsigned int faceCountTarget);

    GLuint getVAO() { return vao;}
    GLuint getVBO() { return vbo;}
    GLuint getNBO() { return nbo;}
    GLuint getEBO() { return ebo;}


private:
    GLuint vao;
    GLuint vbo;
    GLuint nbo;
    GLuint uvo;
    GLuint ebo;

    MyMesh _mesh;

};

#endif
