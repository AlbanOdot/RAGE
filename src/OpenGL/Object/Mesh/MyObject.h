#ifndef MYOBJECT_H
#define MYOBJECT_H
#include "./src/OpenGL/opengl_stuff.h"
#include <OpenMesh/Core/Mesh/TriMesh_ArrayKernelT.hh>
#include <OpenMesh/Core/Geometry/QuadricT.hh>


typedef OpenMesh::TriMesh_ArrayKernelT<> Mesh;

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
    virtual void subdivideLoop();
    //Return the Error
    virtual float halfEdgeCollapse(const unsigned int faceCountTarget);
    //Return the Error
    virtual float edgeCollapse( const unsigned int faceCountTarget);

    void updateFaceMatrix();
    void updateFaceMatrix(Mesh::VertexHandle& vh);

    //Mesh info
    inline unsigned int faceCount()     { return mesh_m.n_faces();}
    inline unsigned int verticesCount() {return mesh_m.n_vertices();}
    inline unsigned int edgeCount()     {return mesh_m.n_edges();}
    inline unsigned int normalsCount()  {return mesh_m.n_vertices();}
    inline unsigned int indicesCount()  {return mesh_m.n_faces() * 3;}
    GLuint getVAO() { return vao;}
    GLuint getVBO() { return vbo;}
    GLuint getNBO() { return nbo;}
    GLuint getEBO() { return ebo;}
    Mesh& mesh() { return mesh_m;}
    OpenMesh::VPropHandleT<OpenMesh::Geometry::Quadricf>& faceMatrix()  { return face_matrix;}

protected:
    GLuint vao = 0;//vertex array buffer
    GLuint vbo = 0;//vertices
    GLuint nbo = 0;//normals
    GLuint uvo = 0;//uv mapping
    GLuint cro = 0;//color
    GLuint ebo = 0;//topology

    Mesh mesh_m;
    OpenMesh::VPropHandleT<OpenMesh::Geometry::Quadricf> face_matrix;
private:
    //Create/init all of the openGL attributes
    void loadGL();
};
#endif
