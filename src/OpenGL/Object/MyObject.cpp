#include "MyObject.h"
#include <vector>
#include <iostream>

MyObject::MyObject(){}
MyObject::~MyObject(){}

MyObject::MyObject(const std::string& path){
    std::string warn;
    std::string err;
    if (!LoadObj(&attrib_m,&shapes_m,&materials_m,&warn,&err,path.c_str()))
    {
        std::cerr << err;
        exit(1);
    }
    std::cout << warn << std::endl;
    //From there the mesh is loaded
    //We now want to init the VAO and everything
    loadGL();
}

//Create/init all of the openGL attributes
void MyObject::loadGL(){

    // Create the VAO:
    glGenVertexArrays(1, &vao);
    glBindVertexArray(vao);
    int i = 0;
    // Create the VBO for positions:;
    glGenBuffers(1, &vbo);
    glBindBuffer(GL_ARRAY_BUFFER, vbo);
    glBufferData(GL_ARRAY_BUFFER, attrib_m.vertices.size() * sizeof(GLfloat), attrib_m.vertices.data(), GL_STATIC_DRAW);
    glVertexAttribPointer(i, 3, GL_FLOAT, GL_FALSE, 3*sizeof(GLfloat), (GLvoid *)0);
    glEnableVertexAttribArray(i++);

    //IF NORMALS IS EMPTY FILL IT WITH ZEROS
    if(attrib_m.normals.empty()){
        //fill with zeroes
        attrib_m.normals.resize(attrib_m.vertices.size());
        for(int j = 0; j < attrib_m.vertices.size(); j++){
            attrib_m.normals[i] = 0.0f;
        }
    }
    // Create the NBO for normals;
    glGenBuffers(1, &nbo);
    glBindBuffer(GL_ARRAY_BUFFER, nbo);
    glBufferData(GL_ARRAY_BUFFER, attrib_m.normals.size() * sizeof(GLfloat), attrib_m.normals.data(), GL_STATIC_DRAW);
    glVertexAttribPointer(i, 3, GL_FLOAT, GL_FALSE, 3*sizeof(GLfloat), (GLvoid *)0);
    glEnableVertexAttribArray(i++);

    //IF COLORS IS EMPTY FILL IT WITH ZEROS
    if(attrib_m.colors.empty()){
        //fill with zeroes
        attrib_m.colors.resize(attrib_m.vertices.size());
        for(int j = 0; j < attrib_m.vertices.size(); j++){
            attrib_m.colors[i] = 0.0f;
        }
    }
    // Create the CRO for color;
    glGenBuffers(1, &cro);
    glBindBuffer(GL_ARRAY_BUFFER, cro);
    glBufferData(GL_ARRAY_BUFFER, attrib_m.colors.size() * sizeof(GLfloat), attrib_m.colors.data(), GL_STATIC_DRAW);
    glVertexAttribPointer(i, 3, GL_FLOAT, GL_FALSE, 3*sizeof(GLfloat), (GLvoid *)0);
    glEnableVertexAttribArray(i++);

    //IF TEXCOORDS IS EMPTY FILL IT WITH ZEROS
    if(attrib_m.texcoords.empty()){
        //fill with zeroes
        attrib_m.texcoords.resize((attrib_m.vertices.size()  / 3) * 2);
        for(int j = 0; j < (attrib_m.vertices.size()  / 3) * 2; j++){
            attrib_m.texcoords[i] = 0.0f;
        }
    }
    // Create the UVO for textures;
    glGenBuffers(1, &uvo);
    glBindBuffer(GL_ARRAY_BUFFER, uvo);
    glBufferData(GL_ARRAY_BUFFER, attrib_m.texcoords.size() * sizeof(GLfloat), attrib_m.texcoords.data(), GL_STATIC_DRAW);
    glVertexAttribPointer(i, 2, GL_FLOAT, GL_FALSE, 2*sizeof(GLfloat), (GLvoid *)0);
    glEnableVertexAttribArray(i++);

    //From here we suppose that vertex indices, normal indices are in the same order
    std::vector<GLuint> v_indices;
    for( int k = 0; k < shapes_m.size(); ++k){
        std::vector<index_t> &meshIndices = shapes_m[k].mesh.indices;
        v_indices.reserve( meshIndices.size() ); //indices contains a struct wich vertex index, normal index, texture index
        for(int i = 0; i < meshIndices.size(); ++i){
            v_indices.push_back(meshIndices[i].vertex_index);
        }
    }
    // Create the EBO for topology:
    glGenBuffers(1, &ebo);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ebo);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, v_indices.size()*sizeof(GLuint), v_indices.data(), GL_STATIC_DRAW);

    glBindVertexArray(0);
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
void MyObject::object2Mesh(attrib_t &a,shape_t &s, Mesh &mesh){
    const std::vector<float_t>& vertices = a.vertices;
    unsigned int nbVertices = vertices.size();

    //On remplit notre mesh de point en sauvegardant les handle
    std::vector<Mesh::VertexHandle> vHandle;
    vHandle.resize(vertices.size() / 3); //1handle par triplé de points
    for(unsigned int i = 0; i < nbVertices; i += 3)
        vHandle.push_back(mesh.add_vertex(Mesh::Point(vertices[i],vertices[i+1],vertices[i+2])));

    //On donne les faces associer à notre mesh
    unsigned int nbIndex = s.mesh.indices.size();
    for(unsigned int i = 0; i < nbIndex - 2; i += 3)
        mesh.add_face(vHandle[i], vHandle[i+1], vHandle[i+2]);
/*
    //Initialisation de ses propres propriétés
    mesh.request_vertex_normals();
    mesh.request_face_normals();
    mesh.request_face_status();
    mesh.request_edge_status();
    mesh.request_vertex_status();*/

}

//Then we need to load the openMesh into our mesh
void MyObject::mesh2Object(Mesh& _mesh, attrib_t& a, shape_t& s){
    attrib_t na;//Nouvel attribus
    shape_t ns;//Nouvelle shape

    unsigned int i = 0;
    na.vertices.resize(_mesh.n_vertices() * 3);
    na.normals.resize(_mesh.n_vertices() * 3);
    ns.mesh.indices.resize(_mesh.n_faces() * 3);
    _mesh.update_normals();

    for(Mesh::FaceIter f_it = _mesh.faces_begin(); f_it != _mesh.faces_end(); ++f_it){
        for(Mesh::FaceVertexIter fv_it = _mesh.fv_iter(*f_it); fv_it.is_valid(); ++fv_it){
            //Index
            //ns.mesh.indices[i] = {fv_it->idx(),fv_it->idx(),-1};

            //Vertex
            Mesh::Point p = _mesh.point(*fv_it);
            na.vertices[ 3 * fv_it->idx()] = p[0];
            na.vertices[ 3 * fv_it->idx() + 1] = p[1];
            na.vertices[ 3 * fv_it->idx() + 2] = p[2];

            //Normal
            Mesh::Normal n = _mesh.normal(*fv_it);
            na.vertices[ 3 * fv_it->idx()] = n[0];
            na.vertices[ 3 * fv_it->idx() + 1] = n[1];
            na.vertices[ 3 * fv_it->idx() + 2] = n[2];
            ++i;
        }
    }

    //On affecte les propriétées à notre MyObject
    a = na;
    s = ns;
}


//Return the new face count
unsigned int MyObject::subdivideLoop(){
    std::vector<float> subdivCoef = {1.f/16.f, 2.f/16.f, 4.f/16.f};

    Mesh mesh;//The openMesh mesh, half edge and stuff
    //Load this object into the openMesh mesh
    object2Mesh(attrib_m,shapes_m[0],mesh);
/*
    //Actually subdivide here


    //Nouvelle position des anciens points -> converge vers la B-SPLANE
    OpenMesh::VPropHandleT< Mesh::Point > vph_pos;
    OpenMesh::EPropHandleT< Mesh::Point > eph_pos;
    for(Mesh::VertexIter v_it= mesh.vertices_begin(); v_it != mesh.vertices_end(); ++v_it){
        Mesh::Point nPos;//Nouvelle position du point

        //On applique la B-Spline sur le bord
        if( mesh.is_boundary(*v_it)){
            Mesh::HalfedgeHandle heh = mesh.halfedge_handle(*v_it);

            if( heh.is_valid() ){
                Mesh::HalfedgeHandle pheh = mesh.prev_halfedge_handle( heh );
                Mesh::VertexHandle to_vh = mesh.to_vertex_handle( heh ); //Point precedent
                Mesh::VertexHandle from_vh = mesh.from_vertex_handle( pheh );//Point suivant
                nPos = 0.125 * (6.0 * mesh.point(*v_it) + mesh.point(to_vh) + mesh.point(from_vh));
            }else
                return -1;//Return max unsigned int
        }else{
            unsigned int valence = 0;
            //On applique la formule en fonction de la valence
            for( Mesh::VertexVertexIter vv_it = mesh.vv_iter(*v_it); vv_it.is_valid(); ++vv_it){
                ++valence;
                nPos += mesh.point(*vv_it);
            }
            //interpolation
            float b = 3. + 2. * std::cos(2. * M_PI / float(valence));
            float a = (40.0 - b*b) / 64.0;
            nPos = (nPos *  a / float(valence)) + (1-a) * mesh.point(*v_it);

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
            nPos *= 0.5;
        }else{

            nPos = 0.125 * (3 * nPos//3(A+B)
                            //point d'arrivée de la prochaine halfedge
                            + mesh.point(mesh.to_vertex_handle(mesh.next_halfedge_handle(heh))) //Z
                            + mesh.point(mesh.to_vertex_handle(mesh.next_halfedge_handle(oheh)))//C
                            );
        }
        mesh.property(eph_pos, *e_it) = nPos;
    }

    //On va maintenant effectuer l'opération de split décrite plus haut
    //On va créer des edge donc mesh.edges_end() va être corrompu
    Mesh::EdgeIter e_it_end = mesh.edges_end();
    for (Mesh::EdgeIter e_it=mesh.edges_begin(); e_it != e_it_end; e_it){
        //Vu que cette opération n'est pas propre à loop on va faire une fonction
        split_edge(mesh, *e_it,vph_pos, eph_pos);
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
*/


    //mesh2Object(mesh,attrib_m,shapes_m[0]);
    //loadGL();
    //draw();
    return faceCount();
}

void MyObject::split_edge(Mesh& mesh, const Mesh::EdgeHandle& e_it,OpenMesh::VPropHandleT< Mesh::Point >& vph_pos,OpenMesh::EPropHandleT< Mesh::Point >& eph_pos)
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
    midP = (midP + mesh.point(mesh.to_vertex_handle(oheh))) * 0.5; // (A+B) * 0.5 = D

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
        //Si on a fait ca normalement on risque de faire tout le tour du bord (50% de chance)
        for (t_heh = heh; mesh.next_halfedge_handle(t_heh) != oheh; t_heh = mesh.opposite_halfedge_handle(mesh.next_halfedge_handle(t_heh)))
        {}
    }
    else
    {
        //TODO passer ca en boucle si ca marche pas
        //On fait le tour de la face (ici tout le temps 2 étapes car maillage triangulaire)
        t_heh = mesh.next_halfedge_handle(mesh.next_halfedge_handle(oheh));
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

void MyObject::split_face(Mesh &mesh, const Mesh::FaceHandle& f_it){
    Mesh::HalfedgeHandle heh(mesh.next_halfedge_handle(mesh.next_halfedge_handle(mesh.halfedge_handle(f_it))));
    splice( mesh, mesh.halfedge_handle(f_it) );
    splice( mesh, heh );
    splice( mesh, mesh.next_halfedge_handle(mesh.next_halfedge_handle(heh)) );
}

void MyObject::splice( Mesh& mesh, const Mesh::HalfedgeHandle& heh){
    // Define Halfedge Handles
    Mesh::HalfedgeHandle heh1(heh);
    Mesh::HalfedgeHandle heh2(mesh.next_halfedge_handle(mesh.next_halfedge_handle(heh)));//Maillage triangulaire -> mettre une boucle soi ca marche pas
    Mesh::HalfedgeHandle heh3(mesh.next_halfedge_handle(heh));


    Mesh::HalfedgeHandle heh4(mesh.next_halfedge_handle(heh2));
    Mesh::HalfedgeHandle heh5(mesh.new_edge( mesh.to_vertex_handle(heh1), mesh.to_vertex_handle(heh2)));
    Mesh::HalfedgeHandle heh6(mesh.opposite_halfedge_handle(heh5));

    // Old and new Face
    Mesh::FaceHandle     fh_old(mesh.face_handle(heh3));
    Mesh::FaceHandle     fh_new(mesh.new_face());


    // 5-2 6-3 2-4 3-5 4-6
    // Re-Set Handles around old Face
    mesh.set_next_halfedge_handle(heh6, heh3);
    mesh.set_next_halfedge_handle(heh2, heh6);

    mesh.set_face_handle(heh6, fh_old);
    mesh.set_face_handle(heh2, fh_old);
    mesh.set_face_handle(heh3, fh_old);
    mesh.set_halfedge_handle(fh_old, heh6);

    // Re-Set Handles around new Face
    mesh.set_next_halfedge_handle(heh1, heh5);
    mesh.set_next_halfedge_handle(heh5, heh4);

    mesh.set_face_handle(heh1, fh_new);
    mesh.set_face_handle(heh4, fh_new);
    mesh.set_face_handle(heh5, fh_new);

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
float MyObject::halfEdgeCollapse(const unsigned int faceCountTarget){
    //On va sort avec une std::map (key = edge handle, val = error)
    return 0.f;
}
//Return the Error
float MyObject::EdgeCollapse( const unsigned int faceCountTarget){
    //On va sort avec une std::map (key = edge handle, val = error)
    return 0.f;
}

void MyObject::draw(){
    glBindVertexArray(vao);
    glDrawElements(GL_TRIANGLES, shapes_m[0].mesh.indices.size(), GL_UNSIGNED_INT, 0);
    glBindVertexArray(0);
}
