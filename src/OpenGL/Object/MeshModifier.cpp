#include "MeshModifier.h"
#include <iostream>
#include <map>
#define Cast(x) static_cast<Mesh::Point::value_type>(x)
#define VCast(y) OpenMesh::vector_cast<Mesh::Normal>(y)
MeshModifier::MeshModifier()
{

}


/******************************************************************
 *
 *
 *
 *                         FUN WITH MESH
 *
 *
 *
 ******************************************************************/
//Mesh actions
//First we need to load our mesh into OpenMesh
void MeshModifier::object2Mesh(attrib_t &a,shape_t &s, Mesh &mesh){
    const std::vector<float_t>& vertices = a.vertices;
    unsigned int nbVertices = vertices.size();
    mesh.add_property(vph_pos, "vph_pos");
    mesh.add_property(eph_pos, "eph_pos");
    mesh.property(vph_pos);
    mesh.property(eph_pos);
    //On remplit notre mesh de point en sauvegardant les handle
    std::vector<Mesh::VertexHandle> vHandle;
    vHandle.resize(vertices.size() / 3); //1handle par triplé de points
    for(unsigned int i = 0; i < nbVertices; i += 3)
        vHandle[i/3] = mesh.add_vertex(Mesh::Point(vertices[i],vertices[i+1],vertices[i+2]));

    //On donne les faces associées à notre mesh
    unsigned int nbIndex = s.mesh.indices.size();
    for(unsigned int i = 0; i < nbIndex; i += 3){
        //Les handles sont "continue" et croissant donc il y a une bijection entre s.mesh.indice et vHandle
        mesh.add_face(vHandle[s.mesh.indices[i].vertex_index],
                      vHandle[s.mesh.indices[i+1].vertex_index],
                      vHandle[s.mesh.indices[i+2].vertex_index]);
    }

    //Initialisation de ses propres propriétés
    mesh.request_vertex_normals();
    mesh.request_face_normals();
    mesh.request_face_status();
    mesh.request_edge_status();
    mesh.request_vertex_status();

}

//Then we need to load the openMesh into our mesh
void MeshModifier::mesh2Object(Mesh& mesh, attrib_t& a, shape_t& s){

    a.vertices.clear();
    a.normals.clear();
    s.mesh.indices.clear();
    unsigned int i = 0;

    a.vertices.resize(mesh.n_vertices() * 3);
    a.normals.resize(mesh.n_vertices() * 3);
    s.mesh.indices.resize(mesh.n_faces() * 3);

    mesh.update_normals();
    mesh.update_face_normals();
    for(Mesh::FaceIter f_it = mesh.faces_begin(); f_it != mesh.faces_end(); ++f_it){
        Mesh::Point barycentre(0.0,0.0,0.0);

        for(Mesh::FaceVertexIter fv_it = mesh.fv_iter(*f_it); fv_it; ++fv_it){
            //Index
            s.mesh.indices[i] = {fv_it->idx(),fv_it->idx(),-1};

            //Vertex
            Mesh::Point p = mesh.point(*fv_it);
            barycentre += p;
            a.vertices[ 3 * fv_it->idx()] = p[0];
            a.vertices[ 3 * fv_it->idx() + 1] = p[1];
            a.vertices[ 3 * fv_it->idx() + 2] = p[2];

            //Normal
            Mesh::Normal n = mesh.normal(*fv_it);
            a.normals[ 3 * fv_it->idx()] = n[0];
            a.normals[ 3 * fv_it->idx() + 1] = n[1];
            a.normals[ 3 * fv_it->idx() + 2] = n[2];
            ++i;
        }
        //Face Normal
        Mesh::Normal n = mesh.normal(*f_it);
        real_t d = barycentre.norm();
        real_t x = n[0], y = n[1], z = n[2];
        real_t xy = x*y;
        std::vector<real_t> vals = {x*x, xy, x*z, x*d,
                                         y*y, y*z, y*d,
                                              z*z, z*d,
                                                   d*d};
        a.face_normals.push_back(vals);
    }
}


void MeshModifier::subdivideLoop(MyObject * obj){
    std::cout << "********************************************"<<std::endl;
    std::cout << "*Avant la subdivision :                    *"<<std::endl;
    std::cout << "*Nombre de faces : " << obj->shape(0).mesh.indices.size()/3 <<"   *"<< std::endl;
    std::cout << "*Nombre de sommets : "<<obj->attrib().vertices.size() << " *"<<std::endl;
    std::cout << "********************************************"<<std::endl;

    Mesh mesh;//The openMesh mesh, half edge and stuff
    //Load this object into the openMesh mesh
    object2Mesh(obj->attrib(),obj->shape(0),mesh);
    //Nouvelle position des anciens points -> converge vers la B-SPLANE
    for(Mesh::VertexIter v_it= mesh.vertices_begin(); v_it != mesh.vertices_end(); ++v_it){
        Mesh::Point nPos(0.0,0.0,0.0);//Nouvelle position du point
        //On applique la B-Spline sur le bord
        if( mesh.is_boundary(*v_it) ){

            Mesh::HalfedgeHandle heh = mesh.halfedge_handle(*v_it);

            if( heh.is_valid() ){
                Mesh::HalfedgeHandle pheh = mesh.prev_halfedge_handle( heh );
                Mesh::VertexHandle to_vh = mesh.to_vertex_handle( heh ); //Point precedent
                Mesh::VertexHandle from_vh = mesh.from_vertex_handle( pheh );//Point suivant
                nPos = Cast(0.125) *(Cast(6.0) * VCast(mesh.point(*v_it))
                                               + VCast(mesh.point(to_vh))
                                               + VCast(mesh.point(from_vh)));
            }else
                return ;
        }else{
            unsigned int valence = 0;
            //On applique la formule en fonction de la valence
            for( Mesh::VertexVertexIter vv_it = mesh.vv_iter(*v_it); vv_it ; ++vv_it){
                ++valence;
                nPos += VCast(mesh.point(*vv_it));
            }
            //interpolation
            float b = 3. + 2. * std::cos(2. * M_PI / float(valence));
            float a = (40.0 - b*b) / 64.0;
            nPos *=  Cast(a / float(valence));
            nPos += Cast(1-a) * VCast(mesh.point(*v_it));

        }
        mesh.property(vph_pos, *v_it) = nPos;
    }
    //From here every point is updated, now subdivide
    //On calcul la position du nouveau point et on le met dans un EPropHandleT
    //Comme ca on associe à chaque edge son point pour le split  -> Edge(40){P1, P2, nPos} -SPLIT> Edge(40){P1,nPos} && Edge(87){nPos,P2}
    for (Mesh::EdgeIter e_it=mesh.edges_begin(); e_it != mesh.edges_end(); ++e_it){
        Mesh::HalfedgeHandle heh = mesh.halfedge_handle( *e_it, 0 );
        Mesh::HalfedgeHandle oheh = mesh.halfedge_handle( *e_it, 1);
        Mesh::Point nPos(mesh.point(mesh.to_vertex_handle(heh)));
        nPos += mesh.point(mesh.to_vertex_handle(oheh)); //A+B
        //2 cas  : 1. Bord -> on le met au milieu nPos = A+B / 2
        //         2. Pas Bord -> on prend le point apres (B) heh et apres oheh (Z) -> (3(A+B)+C+Z)/8
        if(mesh.is_boundary(*e_it)){
            nPos *= Cast(0.5);
        }else{

            nPos = Cast(0.125)
                            * (Cast(3.) * nPos//3(A+B)
                            //point d'arrivée de la prochaine halfedge
                            + VCast(mesh.point(mesh.to_vertex_handle(mesh.next_halfedge_handle(heh)))) //Z
                            + VCast(mesh.point(mesh.to_vertex_handle(mesh.next_halfedge_handle(oheh))))//C
                            );
        }
        mesh.property(eph_pos, *e_it) = nPos;
    }

    //On va maintenant effectuer l'opération de split décrite plus haut
    //On va créer des edge donc mesh.edges_end() va être corrompu
    Mesh::EdgeIter e_it_end = mesh.edges_end();

    for ( Mesh::EdgeIter e_it=mesh.edges_begin(); e_it != e_it_end; ++e_it){
        //Vu que cette opération n'est pas propre à loop on va faire une fonction
        split_edge(mesh, *e_it);
    }
    //Même principe
    Mesh::FaceIter f_it_end   = mesh.faces_end();
    for (Mesh::FaceIter f_it = mesh.faces_begin(); f_it != f_it_end; ++f_it){
        //Vu que cette opération n'est pas propre à loop on va faire une fonction
        split_face(mesh, *f_it );
    }
    //On vient appliquer les changement à notre geometrie
    for ( Mesh::VertexIter v_it  = mesh.vertices_begin(); v_it != mesh.vertices_end(); ++v_it) {
        mesh.set_point(*v_it, mesh.property( vph_pos, *v_it ) );
    }
    mesh2Object(mesh,obj->attrib(),obj->shape(0));
    std::cout << "********************************************"<<std::endl;
    std::cout << "*Apres la subdivision :                    *"<<std::endl;
    std::cout << "*Nombre de faces : " << obj->shape(0).mesh.indices.size()/3 <<"   *"<< std::endl;
    std::cout << "*Nombre de sommets : "<<obj->attrib().vertices.size() << " *"<<std::endl;
    std::cout << "********************************************"<<std::endl<<std::endl<<std::endl;

}

void MeshModifier::split_edge(Mesh& mesh, const Mesh::EdgeHandle& e_it)
{
    /*
     *
     *                                      heh ->
     *          Z ----------------- A ----------------- B ----------------- C
     *                                      <- oheh
     *
     */

    Mesh::HalfedgeHandle heh(mesh.halfedge_handle(e_it, 0));
    Mesh::HalfedgeHandle oheh(mesh.halfedge_handle(e_it, 1));
    Mesh::Point midP(mesh.point(mesh.to_vertex_handle(heh))); // A
    midP = (midP + mesh.point(mesh.to_vertex_handle(oheh))) * Cast(0.5); // (A+B) * 0.5 = D

    // new vertex
    Mesh::VertexHandle vh(mesh.new_vertex( midP ));
    // memorize position, will be set later
    mesh.property( vph_pos, vh ) = mesh.property( eph_pos, e_it );
    // Re-link mesh entities
    Mesh::HalfedgeHandle t_heh;
    if (mesh.is_boundary(e_it))
    {
        //On prend le voisin arrivant sur oheh en parcourant les arretes du sommet suivant heh.
        //On a exactement valence - 1  étapes pour le trouver ce qui est raisonable
        //Si on a fait ca "normalement" on risque de faire tout le tour du bord (50% de chance)
        for (t_heh = heh; mesh.next_halfedge_handle(t_heh) != oheh; t_heh = mesh.opposite_halfedge_handle(mesh.next_halfedge_handle(t_heh)))
        {}
    }
    else
    {
        //On fait le tour de la face (ici tout le temps 2 étapes car maillage triangulaire)
        //t_heh = mesh.next_halfedge_handle(mesh.next_halfedge_handle(oheh)); -> Ca marche pas
       for (t_heh = mesh.next_halfedge_handle(oheh);
                   mesh.next_halfedge_handle(t_heh) != oheh;
                   t_heh = mesh.next_halfedge_handle(t_heh) )
              {}
    }

    //On va faire les mêmes opérations que sur une liste doublement chainé
    Mesh::VertexHandle vh1(mesh.to_vertex_handle(heh)); //vh1 = handle(A)
    Mesh::HalfedgeHandle nheh(mesh.new_edge(vh, vh1));
    Mesh::HalfedgeHandle noheh(mesh.opposite_halfedge_handle(nheh));
    mesh.set_vertex_handle( heh, vh ); //heh pointe vers D et plus sur B
    mesh.set_next_halfedge_handle(t_heh, noheh); //t_heh précede noheh et plus oheh
    mesh.set_next_halfedge_handle(nheh, mesh.next_halfedge_handle(heh)); //nheh précede la suivante de heh
    mesh.set_next_halfedge_handle(heh, nheh);//heh precede nheh
    mesh.set_next_halfedge_handle(noheh, oheh); //noheh precede oheh

    /*
    *
    *                                      nheh ->
    *          Z ----------------- A ----------------- D ----------------- B ----------------- C
    *                                   <- noheh
    */

    //Si la face de l'ancienne he opposé est toujorus valide
    if (mesh.face_handle(oheh).is_valid())
    {
        //On donne cette face au nouveau he opposé
        mesh.set_face_handle(noheh, mesh.face_handle(oheh));
        //On donne le nouveau he opposé à la face  aussi
        mesh.set_halfedge_handle(mesh.face_handle(noheh), noheh);
    }
    //On met à jours les arretes des faces
    mesh.set_face_handle( nheh, mesh.face_handle(heh) );//Même principe
    mesh.set_halfedge_handle( vh, nheh); //Ajoute à la face à laquelle il manque un he nheh
    mesh.set_halfedge_handle( mesh.face_handle(heh), heh );
    mesh.set_halfedge_handle( vh1, noheh );

    //Prend toutes les he entrant et leur associe une opposée
    mesh.adjust_outgoing_halfedge( vh );
    mesh.adjust_outgoing_halfedge( vh1 );
}

void MeshModifier::split_face(Mesh &mesh, const Mesh::FaceHandle& f_it){
    Mesh::HalfedgeHandle heh = mesh.halfedge_handle(f_it);
    Mesh::HalfedgeHandle N2heh(mesh.next_halfedge_handle(mesh.next_halfedge_handle(heh)));
    Mesh::HalfedgeHandle N4heh(mesh.next_halfedge_handle(mesh.next_halfedge_handle(N2heh)));
    splice( mesh, heh );
    splice( mesh, N2heh );
    splice( mesh, N4heh );
}

void MeshModifier::splice( Mesh& mesh, const Mesh::HalfedgeHandle& heh){
    // Define Halfedge Handles
    Mesh::HalfedgeHandle heh1(heh);
    Mesh::HalfedgeHandle heh5(heh);
    for(    ;mesh.next_halfedge_handle(mesh.next_halfedge_handle(heh5)) != heh;heh5 = mesh.next_halfedge_handle(heh5)){}
    Mesh::HalfedgeHandle heh2(mesh.next_halfedge_handle(heh5));
    Mesh::HalfedgeHandle heh3(mesh.new_edge( mesh.to_vertex_handle(heh1), mesh.to_vertex_handle(heh5)));
    Mesh::HalfedgeHandle heh4(mesh.opposite_halfedge_handle(heh3));
    Mesh::HalfedgeHandle heh6(mesh.next_halfedge_handle(heh));

    // Old and new Face
    Mesh::FaceHandle     fh_old(mesh.face_handle(heh6));
    Mesh::FaceHandle     fh_new(mesh.new_face());

    // Re-Set Handles around old Face
    mesh.set_next_halfedge_handle(heh4, heh6);
    mesh.set_next_halfedge_handle(heh5, heh4);

    mesh.set_face_handle(heh4, fh_old);
    mesh.set_face_handle(heh5, fh_old);
    mesh.set_face_handle(heh6, fh_old);
    mesh.set_halfedge_handle(fh_old, heh4);

    // Re-Set Handles around new Face
    mesh.set_next_halfedge_handle(heh1, heh3);
    mesh.set_next_halfedge_handle(heh3, heh2);

    mesh.set_face_handle(heh1, fh_new);
    mesh.set_face_handle(heh2, fh_new);
    mesh.set_face_handle(heh3, fh_new);

    mesh.set_halfedge_handle(fh_new, heh1);
}
/*
 *
 *
 * Collapse algorithm
 *
 *
 */
//Return the Error
float MeshModifier::halfEdgeCollapse(MyObject * obj, const unsigned int faceCountTarget){
    //On va sort avec une std::map (key = edge handle, val = error)
    return 0.0;
}
//Return the Error
float MeshModifier::edgeCollapse(MyObject * obj, const unsigned int faceCountTarget){
    if( faceCountTarget > obj->faceCount())
        return 0.f;

    Mesh mesh;
    object2Mesh(obj->attrib(),obj->shape(0),mesh);
    //Creation of the map
    std::map<float,Mesh::HalfedgeHandle> errorMap;
    //Initialisation
    computeQuadricError(mesh, obj->attrib().face_normals, errorMap);


    //On va sort avec une std::map (key = edge handle, val = error)
    return 0.0;
}

void MeshModifier::computeQuadricError( Mesh& mesh, std::vector<std::vector<float>> faceMatrix, std::map<float, Mesh::HalfedgeHandle>& map){

    //On va associer à chaque edge une erreur
    for (Mesh::EdgeIter e_it=mesh.edges_begin(); e_it!=mesh.edges_end(); ++e_it){
        Mesh::HalfedgeHandle heh(mesh.halfedge_handle(*e_it, 0));
        //On iter sur les voisins direct des vertices du halfedge
        Mesh::VertexHandle to_vh = mesh.to_vertex_handle(heh);
        Mesh::VertexHandle from_vh = mesh.from_vertex_handle(heh);
        //Afin de pas compter deux fois les faces du edge on va les sauvegarder dans un coin
        std::vector<Mesh::FaceHandle> seen;
        //La matrice Q
        float Q[10] = {0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0};

        //Loop du to_vh
        for(Mesh::VertexFaceIter vf_it = mesh.vf_iter(to_vh); vf_it; ++vf_it){
            Mesh::FaceHandle fh(*vf_it);
            //On traite tyoute sles faces autour de to_vh
            seen.push_back(fh);//Ajoute aux faces traitées
            for(int i = 0; i < 9; ++i){
                Q[i] += faceMatrix[fh.idx()][i];
            }
        }
        //Loop du from_vh
        for(Mesh::VertexFaceIter vf_it= mesh.vf_iter(from_vh); vf_it; ++vf_it){
            Mesh::FaceHandle fh(*vf_it);
            //Si on a jamais traité la face
            if(std::find(seen.begin(), seen.end(), fh) == seen.end()){
                for(int i = 0; i < 9; ++i){
                    Q[i] += faceMatrix[fh.idx()][i];
                }
             }
        }

        //Calcul de x,y,z
        float inv_detA = 1.0/(Q[1] * Q[1] * ( Q[5] - Q[7]));
        float x = ((Q[3]*Q[4]*Q[7] + (Q[1]*Q[8] + Q[2]*Q[6]) * Q[5]) - (Q[8] * Q[4] * Q[2] + Q[5]*Q[5]*Q[3] + Q[7]*Q[6]*Q[1])) * inv_detA;
        float y = ((Q[0]*Q[6]*Q[7] + (Q[3]*Q[5] + Q[1]*Q[8]) * Q[2]) - (Q[2] * Q[6] * Q[2] + Q[8]*Q[5]*Q[0] + Q[7]*Q[3]*Q[1])) * inv_detA;
        float z = ((Q[0]*Q[4]*Q[8] + (Q[6]*Q[2] + Q[3]*Q[5]) * Q[1]) - (Q[2] * Q[4] * Q[3] + Q[5]*Q[6]*Q[0] + Q[8]*Q[1]*Q[1])) * inv_detA;

        float Ev = x*x*Q[0] + y*y*Q[4] + z*z*Q[7] + 2*x*y*Q[1] + 2*y*z*Q[5] + 2*x*z*Q[2] + 2*x*Q[3] + 2*y*Q[6] + 2*z*Q[8] + Q[9];

        //On met l'erreur en clef comme ca on tri en insérant.
        //Proba que 2 Erreurs soit les même +- 0%
        //De toute facon on aurait pris la première insérée car on veut un tri en place
        map.insert(std::pair<float,Mesh::HalfedgeHandle>(Ev,heh));
    }
}

