#ifndef SHADERICOSPHERE_H
#define SHADERICOSPHERE_H

#include "scene.h"

#include "../hello_camera/camera.h"

#include <memory>
#include <functional>

class ShaderICOSphere : public Scene
{
public:
    ShaderICOSphere(const int width, const int height);
    void resize(int width, int height) override;
    void draw() override;

    void mouseclick(int button, float xpos, float ypos) override;
    void mousemove(float xpos, float ypos) override;
    void keyboardmove(int key, double time) override;
    bool keyboard(unsigned char k) override;
    inline void addVertex(const glm::vec3& vertex);
    inline void addNormal(const float x, const float y, const float z);
    inline void addTriangle(const int a, const int b, const int c);
    void ICOinitialisation();
    void initFragmentShader(GLuint& prog, const char * shaderSource, const std::string& error);
    void initShader(GLuint& shader, const char * shaderSource, GLenum  type, const std::string& error);

private:
    std::vector<GLfloat> _vertices;
    std::vector<GLfloat> _normals;
    std::vector<GLuint> _indices;
    // A simple geometry
    GLint subdivisionLevel = 0;

    // OpenGL object for geometry
    GLuint _vao;
    GLuint _vbo;
    GLuint _nbo;
    GLuint _ebo;

    // Shader program for rendering
    GLuint _program;
    //Fragment
    GLuint _programcolor;
    GLuint _programnormal;
    GLuint _programdiffuse;
    GLuint _programerror;
    //Vertex Shader
    GLuint _vertexshader;
    //Tesselation
    GLuint _tessControl;
    GLuint _tessEval;
    //Geometry Shader
    GLuint _geomShader;



    // for mouse management
    int _button; // 0 --> left. 1 --> right. 2 --> middle. 3 --> other
    float _mousex{0};
    float _mousey{0};

    // Camera
    using CameraSelector=std::function<Camera*()>;
    std::vector<CameraSelector> _cameraselector;
    int _activecamera;

    std::unique_ptr<Camera> _camera;

    // matrices
    glm::mat4 _model;
    glm::mat4 _view;
    glm::mat4 _projection;
    glm::mat3 _normalMat;
};

#endif // SHADERICOSPHERE_H
