#ifndef GEOMETRYDISPLAY_H
#define GEOMETRYDISPLAY_H

#include "scene.h"

#include "../hello_camera/camera.h"
#include "./Object/MyModel.h"
#include <memory>
#include <functional>

class GeometryDisplay : public Scene
{
public:
    GeometryDisplay(const int width, const int height);
    void resize(int width, int height) override;
    void draw() override;

    void mouseclick(int button, float xpos, float ypos) override;
    void mousemove(float xpos, float ypos) override;
    void keyboardmove(int key, double time) override;
    bool keyboard(unsigned char k) override;

private:

    std::vector<MyModel> _objects;

    // for mouse management
    int _button; // 0 --> left. 1 --> right. 2 --> middle. 3 --> other
    float _mousex{0};
    float _mousey{0};

    // Camera
    using CameraSelector=std::function<Camera*()>;
    std::vector<CameraSelector> _cameraselector;
    int _activecamera;

    std::unique_ptr<Camera> _camera;

    //Matrices
    glm::mat4 _view;
    glm::mat4 _projection;
};

#endif // SHADERICOSPHERE_H
