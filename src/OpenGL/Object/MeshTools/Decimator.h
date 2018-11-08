#ifndef DECIMATOR_H
#define DECIMATOR_H

#include <OpenMesh/Core/Mesh/TriMesh_ArrayKernelT.hh>
#include "./src/OpenGL/Object/Mesh/MyObject.h"

class Decimator
{
public:
    Decimator();
    //Simplification startegy
    virtual float halfEdgeCollapse( MyObject& obj,  const unsigned int faceCountTarget);
    virtual float edgeCollapse( MyObject& obj,  const unsigned int faceCountTarget);

private:
    //Data improvement
    void updateFaceMatrix(MyObject& obj);
    void updateNormals(MyObject& obj);
    //Practical functions
    void computeQuadricError( Mesh& mesh, const OpenMesh::VPropHandleT<OpenMesh::Geometry::Quadricf>& faceMatrix, std::map<float, Mesh::HalfedgeHandle>& map, bool halfEdgeCollapse = true);
    Mesh::Point computeQuadricErrorNewPosition( Mesh& mesh, const OpenMesh::VPropHandleT<OpenMesh::Geometry::Quadricf>& faceMatrix, Mesh::HalfedgeHandle);
    bool collapsable(Mesh& mesh, Mesh::HalfedgeHandle heh);
    float max_error_m = 0.00001;

};

#endif // DECIMATOR_H
