#ifndef Renderer_H
#define Renderer_H

#include "scene.h"

#include "./src/OpenGL/Camera/camera.h"
#include "./src/OpenGL/Textures/framebuffer.h"
#include "./src/OpenGL/Textures/Gbuffer.h"
#include "./src/OpenGL/Textures/ssaoframebuffer.h"
#include "./src/OpenGL/Object/Mesh/MyObject.h"
#include "./src/OpenGL/ShadersUtils/shadermanager.h"

#include <memory>
#include <functional>
typedef struct _quad{
    std::vector<GLfloat> vertices = {-1.0,-1.0,
                                     1.f,-1.0,
                                     1.0, 1.0,
                                     -1.0, 1.0};
    std::vector<GLfloat> uv = {0.0,0.0,
                               1.0,0.0,
                               1.0,1.0,
                               0.0,1.0};

    std::vector<GLuint> indices = {0,1,2,
                                   0,2,3};
    GLuint vao;
    GLuint vbo;
    GLuint ebo;
    GLuint uvbo;
    void quadLoad() {
        // Create the VAO:
        if(!vao)
            glGenVertexArrays(1, &vao);
        glBindVertexArray(vao);
        unsigned int i = 0;
        // Create the VBO for positions:;
        glDeleteBuffers(1,&vbo);//ne raise pas d'erreur si le buffer existe pas
        glGenBuffers(1, &vbo);
        glBindBuffer(GL_ARRAY_BUFFER, vbo);
        glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(GLfloat), vertices.data(), GL_STATIC_DRAW);
        glVertexAttribPointer(i, 3, GL_FLOAT, GL_FALSE, 2*sizeof(GLfloat), (GLvoid *)0);
        glEnableVertexAttribArray(i++);

        //IF TEXCOORDS IS EMPTY FILL IT WITH ZEROS
        // Create the UVO for textures;
        glDeleteBuffers(1,&uvbo);
        glGenBuffers(1, &uvbo);
        glBindBuffer(GL_ARRAY_BUFFER, uvbo);
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

    void quadDraw(){
        glBindVertexArray(vao);
        glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
        glBindVertexArray(0);
    }

} Quad;

class Renderer : public Scene
{
public:
    Renderer(const int width, const int height,const std::string& filename);
    Renderer(const int width, const int height) : Scene(width,height){}
    void resize(int width, int height) override;
    void draw() override;

    void mouseclick(int button, float xpos, float ypos) override;
    void mousemove(float xpos, float ypos) override;
    void keyboardmove(int key, double time) override;
    bool keyboard(unsigned char k) override;
    void wheelEvent( const int down) override;
    void resizeBuffers(int w, int h);

    //INIT
    void initPreprocess();
    void initSSAO();
    void initHDR();
    void initBloom();
    void initFXAA();
    void initLighting();

private:

    //Change this to vector if you need multiple objects
    std::vector<MyObject> m_objects;

    //PostProcess stuff
    Quad m_postProcessScreen;
    GBuffer m_GBuffer;
    FrameBuffer renderBuffer;
    float LiPosition[60*3];
    float LiColor[60*3];
    int nbLights;
    GLuint RENDERPROG;
    float invSS[2] = {static_cast<float>(1.0/ (2*_width)), static_cast<float>(1.0/(2*_height))};

    //SSAO
    SSAOFrameBuffer ssaoBuffer;
    SSAOFrameBuffer ssaoBufferBlur;
    float ssaoKernel[64*3];
    float ssaoNoise[16*3];
    GLuint noiseTexture;
    float ssaoRadius;
    float ssaoBias;
    bool computeSSAO;

    // FXAA
    GLuint FXAAPROG;
    FrameBuffer fxaaBuffer;
    float maxThresholdFXAA;
    float minThresholdFXAA;
    bool showContourFXAA;
    bool computeFXAA;

    // HDR
    GLuint HDRPROG;
    FrameBuffer hdrBuffer;
    float gammaHDR;
    float exposureHDR;
    bool computeHDR;

    // BLOOM
    GLuint BLOOMPROG;
    GLuint BLURPROG;
    FrameBuffer bloomBuffer;
    FrameBuffer blurBufferVert;
    FrameBuffer blurBufferHori;
    unsigned int nbKernelBloom;
    bool computeBLOOM;


    //Shaders
    ShaderManager programs;

    // for mouse management
    int _button; // 0 --> left. 1 --> right. 2 --> middle. 3 --> other
    float _mousex{0};
    float _mousey{0};

    // Camera
    std::unique_ptr<Camera> _camera;

    //Matrices
    glm::mat4 _view;
    glm::mat4 _projection;

    //

    char wireframe = 0;
};



#endif // SHADERICOSPHERE_H
