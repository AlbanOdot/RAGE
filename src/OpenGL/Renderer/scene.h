#ifndef SCENE_H
#define SCENE_H


#include <vector>
#include "./src/OpenGL/opengl_stuff.h"

/** Simple classe for managing an OpenGL scene
 */
enum ButtonMouse{LEFT_BUTTON = 0, RIGHT_BUTTON = 1, MIDDLE_BUTTON = 2, NO_BUTTON = 3};
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
  float lastX[3],lastY[3];
  bool firstMouse[3];
  int m_last_button = 0;
};


#endif // SCENE_H
