#include "MyObject.h"
#include <vector>
#include <iostream>

MyObject::MyObject(){}
MyObject::~MyObject(){}

//Create/init all of the openGL attributes
void MyObject::loadGL(){
    _mesh.n_vertices();
    std::vector<GLfloat> vertices = std::vector<GLfloat>(_mesh.n_vertices()*3); //Vertices
    std::vector<GLfloat> normals = std::vector<GLfloat>(_mesh.n_vertices()*3); //Normals
    std::vector<GLfloat> uv; //TODO : Prendre en compte les textures -> plus tard osef là
   _topology  = std::vector<GLuint>(_mesh.n_faces()*3); //Indices;
    MyMesh::Point p;
    MyMesh::Point nn;
    unsigned int i = 0;
    _mesh.update_normals();

    //On iter sur chaque face -> on va repeter des données mais obligé pour la topo
    for (MyMesh::FaceIter f_it = _mesh.faces_begin(); f_it != _mesh.faces_end(); ++f_it) {
        MyMesh::FaceVertexIter fv_it;
        //on iter sur les point d'une face ( fv = Face's vertices )
        for (fv_it = _mesh.fv_iter(*f_it); fv_it.is_valid(); ++fv_it) {
            //Indices
            _topology[i] = fv_it->idx();
            //Vertices
            p = _mesh.point(*fv_it);
            vertices[(fv_it->idx()*3)] = p[0];
            vertices[(fv_it->idx()*3)+1] = p[1];
            vertices[(fv_it->idx()*3)+2] = p[2];
            //Normals*
            nn = _mesh.normal(*fv_it);
            normals[(fv_it->idx()*3)] = nn[0];
            normals[(fv_it->idx()*3)+1] = nn[1];
            normals[(fv_it->idx()*3)+2] = nn[2];
        }
    }

    // Create the VAO:
    glGenVertexArrays(1, &vao);
    glBindVertexArray(vao);

    // Create the VBO for positions:;
    glGenBuffers(1, &vbo);
    glBindBuffer(GL_ARRAY_BUFFER, vbo);
    glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(GLfloat), vertices.data(), GL_STATIC_DRAW);
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(GLfloat), (GLvoid *)0);

    // Create the NBO for normals;
    glGenBuffers(1, &nbo);
    glBindBuffer(GL_ARRAY_BUFFER, nbo);
    glBufferData(GL_ARRAY_BUFFER, normals.size() * sizeof(GLfloat), normals.data(), GL_STATIC_DRAW);
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(GLfloat), (GLvoid *)0);

    // Create the EBO for topology:
    glGenBuffers(1, &ebo);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ebo);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, _topology.size()*sizeof(GLfloat), _topology.data(), GL_STATIC_DRAW);

    glBindVertexArray(0);
}

MyObject::MyObject(const std::string& path){
    if (!OpenMesh::IO::read_mesh(_mesh, path.c_str()))
    {
      std::cerr << "read error\n";
      exit(1);
    }
    //From there the mesh is loaded
    //We now want to init the VAO and everything
     loadGL();
}

//Mesh actions
//Return the new face count
unsigned int MyObject::subdivideLoop(){
    return _mesh.n_faces();
}

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
