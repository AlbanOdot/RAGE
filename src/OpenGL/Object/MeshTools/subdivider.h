#ifndef SUBDIVIDER_H
#define SUBDIVIDER_H
#include <OpenMesh/Core/Mesh/TriMesh_ArrayKernelT.hh>
#include "./src/OpenGL/Object/Mesh/MyObject.h"

class Subdivider
{
public:
    Subdivider();
    void Loop(MyObject& obj);
private:
    void split_edge( Mesh& mesh, const Mesh::EdgeHandle& e_it);
    void split_face( Mesh &mesh, const Mesh::FaceHandle& f_it);
    void splice( Mesh& mesh, const Mesh::HalfedgeHandle& heh);

    OpenMesh::VPropHandleT< Mesh::Point > vph_pos;
    OpenMesh::EPropHandleT< Mesh::Point > eph_pos;
};

#endif // SUBDIVIDER_H
