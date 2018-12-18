#ifndef MYOPENGLWIDGET_H
#define MYOPENGLWIDGET_H

#include <QOpenGLWidget>
#include <QOpenGLFunctions_4_1_Core>
#include <QKeyEvent>

#include <memory>
#include <functional>
#include "./src/OpenGL/Renderer/Renderer.h"

class MyOpenGLWidget : public QOpenGLWidget, public QOpenGLFunctions_4_1_Core {

public:
    explicit MyOpenGLWidget(QWidget *parent = 0);

    ~MyOpenGLWidget();

    // OpenGL management
    void initializeGL() override;
    void paintGL() override;
    void resizeGL(int width, int height) override;

    // Event maagement
    void mousePressEvent(QMouseEvent *event) override;
    void mouseMoveEvent(QMouseEvent *event) override;
    void keyPressEvent(QKeyEvent *event) override;
    void wheelEvent(QWheelEvent *event) override;

    // Demo management
    void render(const std::string& filename);
    void render();
    void renderAnimLBSCPU(int metric, int model);
    void renderAnimLBSGPU(int metric, int model);
    void renderAnimQuatCPU(int metric, int model);
    //getters
private :
    std::unique_ptr<Scene> _scene;
    // for event management
    std::int64_t _lastime;
    int m_method;
    int m_metric;
    int m_model;
};

#endif // MYOPENGLWIDGET_H
