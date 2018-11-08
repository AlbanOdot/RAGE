#include "subdivider.h"

#define Cast(x) static_cast<Mesh::Point::value_type>(x)
#define VCast(y) OpenMesh::vector_cast<Mesh::Normal>(y)

Subdivider::Subdivider()
{

}

//Mesh actions
void Subdivider::Loop(MyObject& obj){

    Mesh& mesh = obj.mesh();//The openMesh mesh, half edge and stuff
    mesh.add_property(vph_pos, "vph_pos");
    mesh.add_property(eph_pos, "eph_pos");
    mesh.property(vph_pos);
    mesh.property(eph_pos);
    //Load this object into the openMesh mesh
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

    mesh.remove_property(vph_pos);
    mesh.remove_property(eph_pos);
}

void Subdivider::split_edge(Mesh& mesh, const Mesh::EdgeHandle& e_it)
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

void Subdivider::split_face(Mesh &mesh, const Mesh::FaceHandle& f_it){
    Mesh::HalfedgeHandle heh = mesh.halfedge_handle(f_it);
    Mesh::HalfedgeHandle N2heh(mesh.next_halfedge_handle(mesh.next_halfedge_handle(heh)));
    Mesh::HalfedgeHandle N4heh(mesh.next_halfedge_handle(mesh.next_halfedge_handle(N2heh)));
    splice( mesh, heh );
    splice( mesh, N2heh );
    splice( mesh, N4heh );
}

void Subdivider::splice( Mesh& mesh, const Mesh::HalfedgeHandle& heh){
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
