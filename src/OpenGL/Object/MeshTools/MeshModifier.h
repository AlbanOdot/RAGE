#ifndef MESHMODIFIER_H
#define MESHMODIFIER_H
#include <OpenMesh/Core/Mesh/TriMesh_ArrayKernelT.hh>
#include "./src/OpenGL/Object/Mesh/MyObject.h"
#include "./src/OpenGL/Object/MeshTools/subdivider.h"
#include "./src/OpenGL/Object/MeshTools/Decimator.h"

typedef OpenMesh::TriMesh_ArrayKernelT<> Mesh;

class MeshModifier
{
public:
    MeshModifier();

    //Subdivision strategy
    void subdivideLoop(MyObject& obj);

    //Simplification startegy
    virtual float halfEdgeCollapse( MyObject& obj,  const unsigned int faceCountTarget);
    virtual float edgeCollapse( MyObject& obj,  const unsigned int faceCountTarget);


protected:

private:
    Subdivider subdivider_m;
    Decimator decimator_m;
};

#endif // MESHMODIFIER_H
