#ifndef SCENE_H
#define SCENE_H


#include <vector>
#include "./src/OpenGL/opengl_stuff.h"

/** Simple classe for managing an OpenGL scene
 */
class Scene {

public:
    explicit Scene(int width, int height);
    virtual ~Scene();

    virtual void resize(int width, int height);
    virtual void draw();

    virtual void mouseclick(int button, float xpos, float ypos);
    virtual void mousemove(float xpos, float ypos);
    virtual void keyboardmove(int key, double time);
    virtual bool keyboard(unsigned char k);
    virtual void wheelEvent(const int down);

    void toggledrawmode();

protected:
    // Width and heigth of the viewport
    int _width;
    int _height;
    // Rendering mode (true is filled, false is wireframed
    bool _drawfill;

    // for mouse management
    float m_mouseX_click{0};
    float m_mouseY_click{0};
    float _mousex{0};
    float _mousey{0};
    int _button; // 0 --> left. 1 --> right. 2 --> middle. 3 --> other
};


#endif // SCENE_H
