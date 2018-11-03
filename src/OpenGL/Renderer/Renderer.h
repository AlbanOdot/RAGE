#ifndef Renderer_H
#define Renderer_H

#include "scene.h"

#include "./src/hello_camera/camera.h"
#include "./src/OpenGL/Object/MyModel.h"
#include "./src/OpenGL/Textures/framebuffer.h"

#include <memory>
#include <functional>

class Renderer : public Scene
{
public:
    Renderer(const int width, const int height,const std::string& filename);
    void resize(int width, int height) override;
    void draw() override;

    void mouseclick(int button, float xpos, float ypos) override;
    void mousemove(float xpos, float ypos) override;
    void keyboardmove(int key, double time) override;
    bool keyboard(unsigned char k) override;
    void wheelEvent( const int down) override;

private:

    //Change this to vector if you need multiple objects
    MyModel m_object;
    MyModel m_postProcessScreen;
    FrameBuffer m_frameBuffer;

    // for mouse management
    int _button; // 0 --> left. 1 --> right. 2 --> middle. 3 --> other
    float _mousex{0};
    float _mousey{0};

    // Camera
    std::unique_ptr<Camera> _camera;

    //Matrices
    glm::mat4 _view;
    glm::mat4 _projection;
};

#endif // SHADERICOSPHERE_H
