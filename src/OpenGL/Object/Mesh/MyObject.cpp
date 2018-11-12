#include "MyObject.h"
#include <vector>
#include <iostream>
#include "src/OpenGL/Object/MeshTools/MeshModifier.h"
#include <OpenMesh/Core/IO/MeshIO.hh>

MyObject::MyObject(){}
MyObject::~MyObject(){}

MyObject::MyObject(const std::string& path){
    std::string warn;
    std::string err;
    if (!OpenMesh::IO::read_mesh(mesh_m,path.c_str()))
    {
        std::cerr << "Can't read mesh";
        exit(1);
    }
    if( ! mesh_m.has_face_normals() ){
        mesh_m.request_face_normals();
    }
    //Initialisation de ses propres propriétés
    if( !mesh_m.has_vertex_normals() ){
        mesh_m.request_vertex_normals();
    }
    mesh_m.add_property(face_matrix);
    mesh_m.update_face_normals();
    mesh_m.update_vertex_normals();
    mesh_m.request_face_status();
    mesh_m.request_edge_status();
    mesh_m.request_vertex_status();
    updateFaceMatrix();
    //From there the mesh is loaded
    //We now want to init the VAO and everything
    loadGL();
}

//Create/init all of the openGL attributes
void MyObject::loadGL(){
    //On vide notre mesh dans des std::vector pour openGL
    std::vector<float> vertices,normals,colors,uv;
    std::vector<int> indices;
    vertices.resize(mesh_m.n_vertices() * 3);
    normals.resize(mesh_m.n_vertices() * 3);
    colors.resize(mesh_m.n_vertices() * 3);
    uv.resize(mesh_m.n_vertices() * 2);
    indices.resize(mesh_m.n_faces() * 3);
    if( !mesh_m.has_vertex_texcoords2D())
        mesh_m.request_vertex_texcoords2D();
    if ( !mesh_m.has_vertex_colors() )
        mesh_m.request_vertex_colors();
    unsigned int i = 0;
    for(Mesh::FaceIter f_it = mesh_m.faces_begin(); f_it != mesh_m.faces_end(); ++f_it){
        for(Mesh::FaceVertexIter fv_it = mesh_m.fv_iter(*f_it); fv_it; ++fv_it){
            //Index
            indices[i] = fv_it->idx();

            //Vertex
            Mesh::Point p = mesh_m.point(*fv_it);
            vertices[ 3 * fv_it->idx()] = p[0];
            vertices[ 3 * fv_it->idx() + 1] = p[1];
            vertices[ 3 * fv_it->idx() + 2] = p[2];

            //Normal
            Mesh::Normal n = mesh_m.normal(*fv_it);
            normals[ 3 * fv_it->idx()] = n[0];
            normals[ 3 * fv_it->idx() + 1] = n[1];
            normals[ 3 * fv_it->idx() + 2] = n[2];

            //Color
            Mesh::Color c = mesh_m.color(*fv_it);
            colors[ 3 * fv_it->idx()] = c[0];
            colors[ 3 * fv_it->idx() + 1] = c[1];
            colors[ 3 * fv_it->idx() + 2] = c[2];

            //UV
            Mesh::TexCoord2D t = mesh_m.texcoord2D(*fv_it);
            std::cout << "UV("<<fv_it->idx()<<") : ("<<t[0]<<", "<<t[1]<<")"<<std::endl;
            uv[2 * fv_it->idx() ] = t[0];
            uv[2 * fv_it->idx() + 1 ] = t[1];

            ++i;
        }
    }

    // Create the VAO:
    if(!vao)
        glGenVertexArrays(1, &vao);
    glBindVertexArray(vao);
    i = 0;
    // Create the VBO for positions:;
    glDeleteBuffers(1,&vbo);//ne rais epas d'erreur si le buffer existe pas
    glGenBuffers(1, &vbo);
    glBindBuffer(GL_ARRAY_BUFFER, vbo);
    glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(GLfloat), vertices.data(), GL_STATIC_DRAW);
    glVertexAttribPointer(i, 3, GL_FLOAT, GL_FALSE, 3*sizeof(GLfloat), (GLvoid *)0);
    glEnableVertexAttribArray(i++);

    //IF NORMALS IS EMPTY FILL IT WITH ZEROS
    // Create the NBO for normals;
    glDeleteBuffers(1, &nbo);
    glGenBuffers(1, &nbo);
    glBindBuffer(GL_ARRAY_BUFFER, nbo);
    glBufferData(GL_ARRAY_BUFFER, normals.size() * sizeof(GLfloat), normals.data(), GL_STATIC_DRAW);
    glVertexAttribPointer(i, 3, GL_FLOAT, GL_FALSE, 3*sizeof(GLfloat), (GLvoid *)0);
    glEnableVertexAttribArray(i++);

    //IF COLORS IS EMPTY FILL IT WITH ZEROS
    // Create the CRO for color;
    glDeleteBuffers(1,&cro);
    glGenBuffers(1, &cro);
    glBindBuffer(GL_ARRAY_BUFFER, cro);
    glBufferData(GL_ARRAY_BUFFER, colors.size() * sizeof(GLfloat), colors.data(), GL_STATIC_DRAW);
    glVertexAttribPointer(i, 3, GL_FLOAT, GL_FALSE, 3*sizeof(GLfloat), (GLvoid *)0);
    glEnableVertexAttribArray(i++);

    //IF TEXCOORDS IS EMPTY FILL IT WITH ZEROS
    // Create the UVO for textures;
    glDeleteBuffers(1,&uvo);
    glGenBuffers(1, &uvo);
    glBindBuffer(GL_ARRAY_BUFFER, uvo);
    glBufferData(GL_ARRAY_BUFFER, uv.size() * sizeof(GLfloat), uv.data(), GL_STATIC_DRAW);
    glVertexAttribPointer(i, 2, GL_FLOAT, GL_FALSE, 2*sizeof(GLfloat), (GLvoid *)0);
    glEnableVertexAttribArray(i++);

    //From here we suppose that vertex indices, normal indices are in the same order
    // Create the EBO for topology:
    glDeleteBuffers(1, &ebo);
    glGenBuffers(1, &ebo);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ebo);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices.size()*sizeof(GLuint), indices.data(), GL_STATIC_DRAW);

    glBindVertexArray(0);
}


void MyObject::draw(){
    glBindVertexArray(vao);
    glDrawElements(GL_TRIANGLES, mesh_m.n_faces() * 3, GL_UNSIGNED_INT, 0);
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

//Return the new face count
void MyObject::subdivideLoop(){
    std::cout << "********************************************"<<std::endl;
    std::cout << "*Avant la subdivision :                    *"<<std::endl;
    std::cout << "*Nombre de faces : " << faceCount() <<"   *"<< std::endl;
    std::cout << "*Nombre de sommets : "<<verticesCount() << " *"<<std::endl;
    std::cout << "********************************************"<<std::endl;
    MeshModifier m;
    m.subdivideLoop(*this);
    mesh_m.update_face_normals();
    mesh_m.update_normals();
    std::cout << "********************************************"<<std::endl;
    std::cout << "*Apres la subdivision :                    *"<<std::endl;
    std::cout << "*Nombre de faces : " << faceCount() <<"   *"<< std::endl;
    std::cout << "*Nombre de sommets : "<<verticesCount() << " *"<<std::endl;
    std::cout << "********************************************"<<std::endl<<std::endl<<std::endl;
    loadGL();
    draw();
}


float MyObject::halfEdgeCollapse(const unsigned int faceCountTarget){
    std::cout << "++++++++++++++++++++++++++++++++++++++++++++"<<std::endl;
    std::cout << "+Avant la simplification :                  "<<std::endl;
    std::cout << "+Nombre de faces : " << faceCount() <<"   +"<< std::endl;
    std::cout << "+Nombre de sommets : "<<verticesCount() << " +"<<std::endl;
    std::cout << "+Objectif : "<< faceCountTarget<< "  +"<<std::endl;
    std::cout << "++++++++++++++++++++++++++++++++++++++++++++"<<std::endl<<std::endl<<std::endl;
    MeshModifier m;
    float error = m.halfEdgeCollapse(*this,faceCountTarget);
    mesh_m.update_face_normals();
    mesh_m.update_normals();
    std::cout << "++++++++++++++++++++++++++++++++++++++++++++"<<std::endl;
    std::cout << "+Apres la simplification :                  "<<std::endl;
    std::cout << "+Nombre de faces : " << faceCount() <<"   +"<< std::endl;
    std::cout << "+Nombre de sommets : "<<verticesCount() << " +"<<std::endl;
    std::cout << "++++++++++++++++++++++++++++++++++++++++++++"<<std::endl<<std::endl<<std::endl;
    loadGL();
    draw();
    return error;
}

//Return the Error
float MyObject::edgeCollapse( const unsigned int faceCountTarget){
    std::cout << "++++++++++++++++++++++++++++++++++++++++++++"<<std::endl;
    std::cout << "+Avant la simplification :                  "<<std::endl;
    std::cout << "+Nombre de faces : " << faceCount() <<"   +"<< std::endl;
    std::cout << "+Nombre de sommets : "<<verticesCount() << " +"<<std::endl;
    std::cout << "+Objectif : "<< faceCountTarget<< "  +"<<std::endl;
    std::cout << "++++++++++++++++++++++++++++++++++++++++++++"<<std::endl<<std::endl<<std::endl;
    MeshModifier m;
    float error = m.edgeCollapse(*this,faceCountTarget);
    mesh_m.update_face_normals();
    mesh_m.update_normals();
    std::cout << "++++++++++++++++++++++++++++++++++++++++++++"<<std::endl;
    std::cout << "+Apres la simplification :                  "<<std::endl;
    std::cout << "+Nombre de faces : " << faceCount() <<"   +"<< std::endl;
    std::cout << "+Nombre de sommets : "<<verticesCount() << " +"<<std::endl;
    std::cout << "++++++++++++++++++++++++++++++++++++++++++++"<<std::endl<<std::endl<<std::endl;
    loadGL();
    draw();
    return error;
}

void MyObject::updateFaceMatrix(){

    for( Mesh::VertexIter v_it = mesh_m.vertices_begin(); v_it != mesh_m.vertices_end(); ++v_it){
        mesh_m.property(face_matrix, *v_it).clear();
    }

    //On utilise le fait que la norm du vecteur normal == air du triangle
    for( Mesh::FaceIter f_it = mesh_m.faces_begin(); f_it != mesh_m.faces_end(); ++f_it){
        Mesh::FaceVertexIter fv_it = mesh_m.fv_iter(*f_it);
        Mesh::VertexHandle vh1 = *fv_it;
        ++fv_it;
        Mesh::VertexHandle vh2 = *fv_it;
        ++fv_it;
        Mesh::VertexHandle vh3 = *fv_it;
        Mesh::Point v1 = mesh_m.point(vh1);
        Mesh::Point v2 = mesh_m.point(vh2);
        Mesh::Point v3 = mesh_m.point(vh3);

        Mesh::Normal n = (v3-v2) % (v3-v1);
        double aire = n.norm();
        n /= aire;
        OpenMesh::Geometry::Quadricf Qv(n,v1);
        Qv *= 0.5 * aire;//On calcul l'air du parallèlogramme mais on a un triangle donc on divise par 2
        mesh_m.property( face_matrix, vh1) += Qv;
        mesh_m.property( face_matrix, vh2) += Qv;
        mesh_m.property( face_matrix, vh3) += Qv;
    }
}

void MyObject::updateFaceMatrix(Mesh::VertexHandle& vh){
    mesh_m.property(face_matrix, vh).clear();
    //On utilise le fait que la norm du vecteur normal == air du triangle
    for(Mesh::VertexFaceIter vf_it = mesh_m.vf_iter(vh); vf_it.is_valid(); ++vf_it){
        if( !mesh_m.status(*vf_it).deleted())
            continue;
        Mesh::FaceVertexIter fv_it = mesh_m.fv_iter(*vf_it);
        Mesh::VertexHandle vh1 = *fv_it;
        ++fv_it;
        Mesh::VertexHandle vh2 = *fv_it;
        ++fv_it;
        Mesh::VertexHandle vh3 = *fv_it;
        Mesh::Point v1 = mesh_m.point(vh1);
        Mesh::Point v2 = mesh_m.point(vh2);
        Mesh::Point v3 = mesh_m.point(vh3);

        Mesh::Normal n = (v3-v2) % (v3-v1);
        double aire = n.norm();
        n /= aire;
        OpenMesh::Geometry::Quadricf Qv(n,v1);
        Qv *= 0.5 * aire;//On calcul l'air du parallèlogramme mais on a un triangle donc on divise par 2
        mesh_m.property( face_matrix, vh) += Qv;
    }
}
