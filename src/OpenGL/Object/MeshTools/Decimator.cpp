#include "Decimator.h"
#include <iostream>
Decimator::Decimator()
{

}

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
    //Creation of the map
    std::map<float,Mesh::HalfedgeHandle> errorMap;
    do{
        //Initialisation
        updateFaceMatrix(obj);
        computeQuadricError(mesh, obj.faceMatrix(), errorMap, false);
        if( errorMap.empty())
            break;
        const std::pair<float,Mesh::HalfedgeHandle>& item = *(errorMap.begin());
        totalError += item.first;
        //Calcul de la nouvelle position de to_vh
        Mesh::Point nPos = computeQuadricErrorNewPosition(mesh, obj.faceMatrix(), item.second);
        Mesh::VertexHandle to_vh(mesh.to_vertex_handle(item.second));
        //On dépalce le point
        mesh.set_point(to_vh, nPos);
        //Ecrase le from_vertex sur le to_vertex
        mesh.collapse(item.second);
        mesh.garbage_collection();
        std::cout << "There is "<< mesh.n_faces() - faceCountTarget << " remaining." << std::endl;
    }while(mesh.n_faces() > faceCountTarget);
    mesh.update_normals();
    return totalError;
}

float Decimator::halfEdgeCollapse(MyObject &obj, const unsigned int faceCountTarget){
    if( faceCountTarget >= obj.faceCount() )
        return 0.f;
    float totalError = 0.0;
    Mesh& mesh = obj.mesh();
    //Creation of the map
    std::map<float,Mesh::HalfedgeHandle> errorMap;
    do{
        //Initialisation
        updateFaceMatrix(obj);
        computeQuadricError(mesh, obj.faceMatrix(), errorMap, true);
        if( errorMap.empty())
            break;
        const std::pair<float,Mesh::HalfedgeHandle>& item = *(errorMap.begin());
        totalError += item.first;
        //Faire un vv_iter et un ev_iter
        //Ecrase le from_vertex sur le to_vertex
        mesh.collapse(item.second);
        mesh.garbage_collection();
        std::cout << "There is "<< mesh.n_faces() - faceCountTarget << " remaining." << std::endl;
    }while(mesh.n_faces() > faceCountTarget);
    mesh.update_normals();
    return totalError;
}

void Decimator::computeQuadricError( Mesh& mesh, const OpenMesh::VPropHandleT<OpenMesh::Geometry::Quadricf>& faceMatrix, std::map<float, Mesh::HalfedgeHandle>& map, bool halfEdgeCollapse){

    map.clear();
    //On va associer à chaque edge une erreur
    for (Mesh::EdgeIter e_it=mesh.edges_begin(); e_it!=mesh.edges_end(); ++e_it){

        Mesh::HalfedgeHandle heh(mesh.halfedge_handle(*e_it, 0));
        float Ev = 0.f;
        Mesh::HalfedgeHandle minheh;
        if( collapsable(mesh, heh)){//On ne met que des heh que l'on peut collapse
            if( halfEdgeCollapse ){
                Mesh::VertexHandle to_vh = mesh.to_vertex_handle(heh);
                Mesh::VertexHandle from_vh = mesh.from_vertex_handle(heh);
                OpenMesh::Geometry::Quadricf Qto =  mesh.property( faceMatrix, to_vh);
                OpenMesh::Geometry::Quadricf Qfrom = mesh.property( faceMatrix, from_vh);
                float Evto = Qto(mesh.point(to_vh));
                float Evfrom = Qfrom(mesh.point(from_vh));
                minheh = Evto < Evfrom ? heh : mesh.opposite_halfedge_handle(heh);
                Ev = Evto < Evfrom ? Evto : Evfrom;
            }else{
                Mesh::VertexHandle to_vh = mesh.to_vertex_handle(heh);
                Mesh::VertexHandle from_vh = mesh.from_vertex_handle(heh);
                OpenMesh::Geometry::Quadricf Q =  mesh.property( faceMatrix, to_vh);
                Q += mesh.property( faceMatrix, from_vh);
                Mesh::Point p = computeQuadricErrorNewPosition(mesh, faceMatrix, heh);//TODO changer ca
                Ev = Q( p );
                minheh = heh;
            }
            if( Ev < max_error_m)
                map.insert(std::pair<float,Mesh::HalfedgeHandle>(Ev,minheh));
            //On met l'erreur en clef comme ca on tri en insérant.
            //Proba que 2 Erreurs soit les même +- 0% -> Solide régulier
            //De toute facon on aurait pris la première insérée car on veut un tri en place
        }
    }
    std::cout << "map size : " << map.size() << std::endl;
}

bool Decimator::collapsable(Mesh& mesh, Mesh::HalfedgeHandle heh){
    if( !mesh.is_collapse_ok(heh) || mesh.is_boundary(heh))
        return false;

    //Voisin de gauche
    Mesh::VertexHandle v0 = mesh.to_vertex_handle(mesh.next_halfedge_handle(heh));
    //Voisin de droite
    Mesh::VertexHandle v1 = mesh.to_vertex_handle(mesh.next_halfedge_handle(mesh.opposite_halfedge_handle(heh)));
    //Test du diamant
    if (v0.is_valid() && v1.is_valid()
            && mesh.find_halfedge(v0, v1).is_valid()
            && mesh.valence(v0) == 3 && mesh.valence(v1) == 3)
        return false;
    //On vaut pas collapse un sommet de bord sur un de l'intérieur
    if( mesh.is_boundary(v0)
            && ( !mesh.is_boundary(v1) || (v0.is_valid() && v1.is_valid() )))
        return false;
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
