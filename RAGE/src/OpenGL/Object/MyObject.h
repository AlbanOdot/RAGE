#ifndef SHADERICOSPHERE_H
#define SHADERICOSPHERE_H

#include <vector>
#include <gl.h>

class MyObject {

public:
    MyObject();
    ~MyObject();

    //Mesh with ligth interaction
    MyObject(const std::vector<GLfloat>& v, const std::vector<GLfloat>& n, const std::vector<GLuint>& t);
    //Mesh simple mesh
    MyObject(const std::vector<GLfloat>& v, const std::vector<GLuint>& t);
    //Points cloud
    MyObject(const std::vector<GLfloat>& v);

    //From points cloud to Mesh
    void addTopology(const std::vector<GLuint>& t);
    //From Mesh to Mesh with light interaction
    void addNormals(const std::vector<GLfloat>& n);
    //From points cloud to mesh with light interaction
    void addNormalsAndTopology(const std::vector<GLfloat>&n, const std::vector<GLuint>& t);

    GLuint getVAO() { return vao;}
    GLuint getVBO() { return vbo;}
    GLuint getNBO() { return nbo;}
    GLuint getEBO() { return ebo;}

    std::vector<GLfloat> getVertices() { return vertices;}
    std::vector<GLfloat> getNormals() { return normals;}
    std::vector<GLuint> getTopology() { return topology;}


private:
    GLuint vao;
    GLuint vbo;
    GLuint nbo;
    GLuint ebo;

    std::vector<GLfloat> vertices;
    std::vector<GLfloat> normals;
    std::vector<GLuint> topology;

};

#endif
