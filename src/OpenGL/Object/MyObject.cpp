#include "MyObject.h"
#include <vector>
#include <iostream>
#include "MeshModifier.h"


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
    if(!vao)
        glGenVertexArrays(1, &vao);
    glBindVertexArray(vao);
    int i = 0;
    // Create the VBO for positions:;
    glDeleteBuffers(1,&vbo);//ne rais epas d'erreur si le buffer existe pas
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
    glDeleteBuffers(1, &nbo);
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
    glDeleteBuffers(1,&cro);
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
    glDeleteBuffers(1,&uvo);
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
    glDeleteBuffers(1, &ebo);
    glGenBuffers(1, &ebo);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ebo);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, v_indices.size()*sizeof(GLuint), v_indices.data(), GL_STATIC_DRAW);

    glBindVertexArray(0);
}


void MyObject::draw(){
    glBindVertexArray(vao);
    glDrawElements(GL_TRIANGLES, shapes_m[0].mesh.indices.size(), GL_UNSIGNED_INT, 0);
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
    MeshModifier m;
    m.subdivideLoop(this);
    loadGL();
    draw();
}
//Return the Error
float MyObject::halfEdgeCollapse(const unsigned int faceCountTarget){
    MeshModifier m;
    return m.halfEdgeCollapse(this,faceCountTarget);
}

//Return the Error
float MyObject::edgeCollapse( const unsigned int faceCountTarget){
    MeshModifier m;
    return m.edgeCollapse(this,faceCountTarget);
}
