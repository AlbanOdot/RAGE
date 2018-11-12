#include "Decimator.h"
#include <iostream>
Decimator::Decimator(){}

void Decimator::updateFaceMatrix(MyObject &obj){
    obj.mesh().update_normals();
    obj.mesh().update_face_normals();
    obj.updateFaceMatrix();
}

void Decimator::updateNormals(MyObject &obj){
    if( ! obj.mesh().has_vertex_normals() )
        obj.mesh().request_vertex_normals();
    obj.mesh().update_vertex_normals();
}

float Decimator::edgeCollapse(MyObject &obj, const unsigned int faceCountTarget){
    if( faceCountTarget >= obj.faceCount() )
        return 0.f;
    float totalError = 0.0;
    Mesh& mesh = obj.mesh();

    mesh.request_vertex_status();
    mesh.request_edge_status();
    mesh.request_face_status();
    //Creation of the map
    std::map<float,Mesh::HalfedgeHandle> errorMap;
    do{
        //Initialisation
        updateFaceMatrix(obj);
        computeQuadricError(mesh, obj.faceMatrix(), errorMap);
        while(!collapsable(mesh,errorMap.begin()->second) && !errorMap.empty()){
            errorMap.erase(errorMap.begin());
        }
        if( errorMap.empty())
            break;
        const std::pair<float,Mesh::HalfedgeHandle>& item = *(errorMap.begin());

        totalError += item.first;
        //Faire un vv_iter et un ev_iter
        Mesh::Point nPos = computeQuadricErrorNewPosition(mesh,obj.faceMatrix(),item.second);
        mesh.set_point(mesh.from_vertex_handle(item.second),nPos);
        //Ecrase le from_vertex sur le to_vertex
        mesh.collapse(item.second);
        mesh.garbage_collection();
    }while(mesh.n_faces() > faceCountTarget);
    mesh.update_normals();
    return totalError;
}

float Decimator::halfEdgeCollapse(MyObject &obj, const unsigned int faceCountTarget){
    if( faceCountTarget >= obj.faceCount() )
        return 0.f;
    float totalError = 0.0;
    Mesh& mesh = obj.mesh();

    mesh.request_vertex_status();
    mesh.request_edge_status();
    mesh.request_face_status();
    //Creation of the map
    std::map<float,Mesh::HalfedgeHandle> errorMap;
    do{
        //Initialisation
        updateFaceMatrix(obj);
        computeQuadricError(mesh, obj.faceMatrix(), errorMap);
        while(!collapsable(mesh,errorMap.begin()->second) && !errorMap.empty()){
            errorMap.erase(errorMap.begin());
        }
        if( errorMap.empty())
            break;
        const std::pair<float,Mesh::HalfedgeHandle>& item = *(errorMap.begin());

        totalError += item.first;
        //Faire un vv_iter et un ev_iter
        //Ecrase le from_vertex sur le to_vertex
        mesh.collapse(item.second);
        mesh.garbage_collection();
    }while(mesh.n_faces() > faceCountTarget);
    mesh.update_normals();
    return totalError;
}

void Decimator::computeQuadricError( Mesh& mesh, const OpenMesh::VPropHandleT<OpenMesh::Geometry::Quadricf>& faceMatrix, std::map<float, Mesh::HalfedgeHandle>& map){

    map.clear();
    //On va associer à chaque edge une erreur
    for (Mesh::EdgeIter e_it=mesh.edges_begin(); e_it!=mesh.edges_end(); ++e_it){

        Mesh::HalfedgeHandle heh(mesh.halfedge_handle(*e_it, 0));
        float Ev = 0.f;
        Mesh::HalfedgeHandle minheh;
        Mesh::VertexHandle to_vh = mesh.to_vertex_handle(heh);
        Mesh::VertexHandle from_vh = mesh.from_vertex_handle(heh);
        OpenMesh::Geometry::Quadricf Q =  mesh.property( faceMatrix, to_vh);
        Q += mesh.property( faceMatrix, from_vh);
        Mesh::Point p = computeQuadricErrorNewPosition(mesh, faceMatrix, heh);//TODO changer ca
        Ev = Q( p );
        minheh = heh;
        map.insert(std::pair<float,Mesh::HalfedgeHandle>(Ev,minheh));
        //On met l'erreur en clef comme ca on tri en insérant.
        //Proba que 2 Erreurs soit les même +- 0% -> Solide régulier
        //De toute facon on aurait pris la première insérée car on veut un tri en place
    }
}

bool Decimator::collapsable(Mesh& mesh, Mesh::HalfedgeHandle heh){
    //Voisin de gauche
    Mesh::VertexHandle v0 = mesh.to_vertex_handle(mesh.next_halfedge_handle(heh));
    //Voisin de droite
    Mesh::VertexHandle v1 = mesh.to_vertex_handle(mesh.next_halfedge_handle(mesh.opposite_halfedge_handle(heh)));
    //Vertex à supprimer
    Mesh::VertexHandle from_vh = mesh.from_vertex_handle(heh);
    //Vertex restant
    Mesh::VertexHandle to_vh = mesh.to_vertex_handle(heh);

    if( mesh.status(from_vh).locked())
        return false;
    if(!mesh.is_collapse_ok(heh))
        return false;
    //Test du diamant
    if (v0.is_valid() && v1.is_valid()
            && mesh.find_halfedge(v0, v1).is_valid()
            && mesh.valence(v0) == 3 && mesh.valence(v1) == 3)
        return false;

    if( mesh.status(from_vh).feature() && !mesh.status(mesh.edge_handle(heh)).feature())
        return false;

    //On vaut pas collapse un sommet de bord sur un de l'intérieur
    if( mesh.is_boundary(from_vh)){

        if( !mesh.is_boundary(to_vh) )
            return false;
        if(v0.is_valid() && v1.is_valid() )
            return false;
    }
    //Il manque surement une condition de bord

    //2 faces incidentes au moins
    return mesh.cw_rotated_halfedge_handle( mesh.cw_rotated_halfedge_handle(heh)) != heh;
}

template <typename T> int sgn(T val) {
    return (T(0) < val) - (val < T(0));
}

Mesh::Point Decimator::computeQuadricErrorNewPosition( Mesh& mesh, const OpenMesh::VPropHandleT<OpenMesh::Geometry::Quadricf>& faceMatrix, Mesh::HalfedgeHandle heh){

    Mesh::VertexHandle to_vh = mesh.to_vertex_handle(heh);
    Mesh::VertexHandle from_vh = mesh.from_vertex_handle(heh);
    OpenMesh::Geometry::Quadricf Q =  mesh.property( faceMatrix, to_vh);
    Q += mesh.property( faceMatrix, from_vh);

    auto det = [](const OpenMesh::Vec3f& x, const OpenMesh::Vec3f& y, const OpenMesh::Vec3f& z) -> float{
        return x[0]*y[1]*z[2] + x[2]*y[0]*z[1] + x[1]*y[2]*z[0] - x[2]*y[1]*z[0] - x[0]*y[2]*z[1] - x[1]*y[0]*z[2]; };

    OpenMesh::Vec3f X(Q.xx(),Q.xy(),Q.xz());
    OpenMesh::Vec3f Y(Q.xy(),Q.yy(),Q.yz());
    OpenMesh::Vec3f Z(Q.xz(),Q.yz(),Q.zz());
    OpenMesh::Vec3f B(-Q.xw(),-Q.yw(),-Q.zw());
    float d = det(X,Y,Z);
    float invDetA = 1.0 / d;
    float x = det(B,Y,Z) * invDetA;
    float y = det(X,B,Z) * invDetA;
    float z = det(X,Y,B) * invDetA;
    Mesh::Point p(x,y,z);
    return p;
}
