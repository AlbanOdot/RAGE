#include "MyObject.h"
#include <vector>
#include <iostream>
#include "MeshModifier.h"
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
    m.subdivideLoop(this);
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
//Return the Error
float MyObject::halfEdgeCollapseMinError(const unsigned int faceCountTarget){
    std::cout << "++++++++++++++++++++++++++++++++++++++++++++"<<std::endl;
    std::cout << "+Avant la simplification :                  "<<std::endl;
    std::cout << "+Nombre de faces : " << faceCount() <<"   +"<< std::endl;
    std::cout << "+Nombre de sommets : "<<verticesCount() << " +"<<std::endl;
    std::cout << "+Objectif : "<< faceCountTarget<< "  +"<<std::endl;
    std::cout << "++++++++++++++++++++++++++++++++++++++++++++"<<std::endl<<std::endl<<std::endl;
    MeshModifier m;
    float error = m.halfEdgeCollapseMinError(this,faceCountTarget);
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
float MyObject::edgeCollapseMinError( const unsigned int faceCountTarget){
    std::cout << "++++++++++++++++++++++++++++++++++++++++++++"<<std::endl;
    std::cout << "+Avant la simplification :                  "<<std::endl;
    std::cout << "+Nombre de faces : " << faceCount() <<"   +"<< std::endl;
    std::cout << "+Nombre de sommets : "<<verticesCount() << " +"<<std::endl;
    std::cout << "+Objectif : "<< faceCountTarget<< "  +"<<std::endl;
    std::cout << "++++++++++++++++++++++++++++++++++++++++++++"<<std::endl<<std::endl<<std::endl;
    MeshModifier m;
    float error = m.edgeCollapseMinError(this,faceCountTarget);
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

float MyObject::fastHalfEdgeCollapse(const unsigned int faceCountTarget){
    std::cout << "++++++++++++++++++++++++++++++++++++++++++++"<<std::endl;
    std::cout << "+Avant la simplification :                  "<<std::endl;
    std::cout << "+Nombre de faces : " << faceCount() <<"   +"<< std::endl;
    std::cout << "+Nombre de sommets : "<<verticesCount() << " +"<<std::endl;
    std::cout << "+Objectif : "<< faceCountTarget<< "  +"<<std::endl;
    std::cout << "++++++++++++++++++++++++++++++++++++++++++++"<<std::endl<<std::endl<<std::endl;
    MeshModifier m;
    float error = m.fastHalfEdgeCollapse(this,faceCountTarget);
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
float MyObject::fastEdgeCollapse( const unsigned int faceCountTarget){
    std::cout << "++++++++++++++++++++++++++++++++++++++++++++"<<std::endl;
    std::cout << "+Avant la simplification :                  "<<std::endl;
    std::cout << "+Nombre de faces : " << faceCount() <<"   +"<< std::endl;
    std::cout << "+Nombre de sommets : "<<verticesCount() << " +"<<std::endl;
    std::cout << "+Objectif : "<< faceCountTarget<< "  +"<<std::endl;
    std::cout << "++++++++++++++++++++++++++++++++++++++++++++"<<std::endl<<std::endl<<std::endl;
    MeshModifier m;
    float error = m.fastEdgeCollapse(this,faceCountTarget);
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

    if(!mesh_m.has_face_normals())
        mesh_m.request_face_normals();
    mesh_m.update_face_normals();

    face_matrix.resize(mesh_m.n_faces());
    for(Mesh::FaceIter f_it = mesh_m.faces_begin(); f_it != mesh_m.faces_end(); ++f_it){
        Mesh::Point barycentre(0.0,0.0,0.0);
        for(Mesh::FaceVertexIter fv_it = mesh_m.fv_iter(*f_it); fv_it; ++fv_it){
            barycentre += mesh_m.point(*fv_it);
        }
        //Face Normal
        Mesh::Normal n = mesh_m.normal(*f_it);
        barycentre = barycentre/3.f;
        float d = barycentre.norm();
        float x = n[0], y = n[1], z = n[2];
        std::vector<float> Qv = {x*x, x*y, x*z, x*d,
                                         y*y, y*z, y*d,
                                              z*z, z*d,
                                                   d*d};
        face_matrix[f_it->idx()] = Qv;
    }
}
