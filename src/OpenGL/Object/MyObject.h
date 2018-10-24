#ifndef MYOBJECT_H
#define MYOBJECT_H
#include <OpenMesh/Core/IO/MeshIO.hh>
#include <OpenMesh/Core/Mesh/TriMesh_ArrayKernelT.hh>
#include <OpenMesh/Tools/Subdivider/Uniform/Composite/CompositeTraits.hh>
#include "./opengl_stuff.h"

typedef OpenMesh::TriMesh_ArrayKernelT<>  MyMesh;

class MyObject {

public:
    MyObject();
    ~MyObject();

    //Mesh from a file
    MyObject(const std::string& path);

    //Mesh actions
    //Return the new face count
    virtual unsigned int subdivideLoop();
    //Return the Error
    virtual float halfEdgeCollapse(const unsigned int faceCountTarget);
    //Return the Error
    virtual float EdgeCollapse( const unsigned int faceCountTarget);

    //Mesh info
    inline unsigned int faceCount() {return _mesh.n_faces();}
    inline unsigned int verticesCount() {return _mesh.n_vertices();}
    inline unsigned int edgeCount() { return _mesh.n_faces() * 3;}
    inline unsigned int normalsCount() {return verticesCount();}
    inline unsigned int indicesCount() { return _topology.size();}

protected:
    GLuint getVAO() { return vao;}
    GLuint getVBO() { return vbo;}
    GLuint getNBO() { return nbo;}
    GLuint getEBO() { return ebo;}


    std::vector<GLuint> _topology;
    GLuint vao;//vertex array buffer
    GLuint vbo;//vertices
    GLuint nbo;//normals
    GLuint uvo;//uv mapping
    GLuint ebo;//topology

    MyMesh _mesh;//The actual mesh

private:
    //Create/init all of the openGL attributes
    void loadGL();
};

#endif
