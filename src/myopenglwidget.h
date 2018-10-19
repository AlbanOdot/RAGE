#ifndef MYOPENGLWIDGET_H
#define MYOPENGLWIDGET_H

#include <QOpenGLWidget>
#include <QOpenGLFunctions_4_1_Core>
#include <QKeyEvent>

#include <memory>

#include "scene.h"


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

    // Demo management
    void activatedemo(unsigned int numdemo);

private :
    std::unique_ptr<Scene> _scene;

    using DemoConstructors=std::function<Scene*(int, int)>;
    std::vector<DemoConstructors> _democonstructors;

    // for event management
    std::int64_t _lastime;
};

#endif // MYOPENGLWIDGET_H