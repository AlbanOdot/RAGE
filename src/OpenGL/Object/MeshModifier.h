#ifndef MESHMODIFIER_H
#define MESHMODIFIER_H
#include "./src/OpenGL/Object/tiny_obj_loader.h"
#include <OpenMesh/Core/Mesh/TriMesh_ArrayKernelT.hh>
#include "MyObject.h"

using namespace tinyobj;

typedef OpenMesh::TriMesh_ArrayKernelT<> Mesh;

class MeshModifier
{
public:
    MeshModifier();

    //Data improvement
    void computeFaceMatrix(MyObject& obj, Mesh& mesh);
    void recomputeNormals(MyObject& obj, Mesh& mesh);

    //Subdivision strategy
    void subdivideLoop(MyObject* obj);

    //Simplification startegy
    virtual float halfEdgeCollapseMinError( MyObject* obj, const unsigned int faceCountTarget);
    virtual float edgeCollapseMinError( MyObject* obj,  const unsigned int faceCountTarget);
    virtual float fastHalfEdgeCollapse( MyObject* obj,  const unsigned int faceCountTarget);
    virtual float fastEdgeCollapse( MyObject* obj,  const unsigned int faceCountTarget);


protected:

private:
    void mesh2Object( Mesh& mesh, attrib_t& a, shape_t& s);
    void object2Mesh( attrib_t& a, shape_t& s, Mesh& mesh);
    void split_edge( Mesh& mesh, const Mesh::EdgeHandle& e_it);
    void split_face( Mesh &mesh, const Mesh::FaceHandle& f_it);
    void splice( Mesh& mesh, const Mesh::HalfedgeHandle& heh);
    void computeQuadricError( Mesh& mesh, std::vector<std::vector<float>> faceMatrix, std::map<float, Mesh::HalfedgeHandle>& map);

    OpenMesh::VPropHandleT< Mesh::Point > vph_pos;
    OpenMesh::EPropHandleT< Mesh::Point > eph_pos;

};

#endif // MESHMODIFIER_H
