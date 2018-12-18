#include "myopenglwidget.h"

#include <QMessageBox>
#include <QApplication>
#include <QDateTime>

#include <iostream>
#include <stdexcept>

#include "./src/OpenGL/Camera/Camera.hpp"
#include "./src/OpenGL/Renderer/Renderer.h"
#include "./src/OpenGL/Renderer/RendererGPU.h"
#include "./src/OpenGL/Renderer/RendererQuat.h"

MyOpenGLWidget::MyOpenGLWidget(QWidget *parent) :QOpenGLWidget(parent), QOpenGLFunctions_4_1_Core(), _scene(nullptr), _lastime(0) {
  m_method = 0;
  m_metric = 0;
  m_model = 0;
}

MyOpenGLWidget::~MyOpenGLWidget() {

}

void MyOpenGLWidget::initializeGL() {
    if (!initializeOpenGLFunctions()) {
        QMessageBox::critical(this, "OpenGL initialization error", "MyOpenGLWidget::initializeGL() : Unable to initialize OpenGL functions");
        exit(1);
    }
    // Initialize OpenGL and all OpenGL dependent stuff below
    _scene.reset(new Scene(width(), height()));
}

void MyOpenGLWidget::paintGL() {
    std::int64_t starttime = QDateTime::currentMSecsSinceEpoch();
    _scene->draw();
    glFinish();
    std::int64_t endtime = QDateTime::currentMSecsSinceEpoch();
    _lastime = endtime-starttime;
}

void MyOpenGLWidget::resizeGL(int width, int height) {
    _scene->resize(width, height);
}

void MyOpenGLWidget::mousePressEvent(QMouseEvent *event) {
    // buttons are 0(left), 1(right) to 2(middle)
    int b;
    Qt::MouseButton button=event->button();
    if (button & Qt::LeftButton) {
        if ((event->modifiers() & Qt::ControlModifier))
            b = 2;
        else
            b = 0;
    } else if (button & Qt::RightButton)
        b = 1;
    else if (button & Qt::MiddleButton)
        b = 2;
    else
        b=3;
    _scene->mouseclick(b, event->x(), event->y());
    _lastime = QDateTime::currentMSecsSinceEpoch();
}

void MyOpenGLWidget::wheelEvent(QWheelEvent *event){
    QPoint angle = event->angleDelta();
    _scene->wheelEvent(angle.y() / 15);
    event->accept();
    update();
}

void MyOpenGLWidget::mouseMoveEvent(QMouseEvent *event) {
    _scene->mousemove(event->x(), event->y());
    update();
}

void MyOpenGLWidget::keyPressEvent(QKeyEvent *event) {
    switch(event->key()) {
        // Demo keys
        case Qt::Key_1:
        renderAnimLBSCPU(1,0);
        break;
        case Qt::Key_2:
        renderAnimLBSGPU(1,0);
        break;
        case Qt::Key_3:
        renderAnimQuatCPU(1,0);
        break;
        case Qt::Key_4:
        case Qt::Key_5:
        case Qt::Key_6:
        case Qt::Key_7:
        case Qt::Key_8:
        case Qt::Key_9:
        case Qt::Key_0:
        break;
        // Move keys
        case Qt::Key_Left:
        case Qt::Key_Up:
        case Qt::Key_Right:
        case Qt::Key_Down:
            _scene->keyboardmove(event->key()-Qt::Key_Left, double(_lastime)/10.);
            update();
        break;
        // Wireframe key
        case Qt::Key_W:
            _scene->toggledrawmode();
            update();
        break;
    case Qt::Key_Space:
        render();
        break;
        // Other keys are transmitted to the scene
        default :
            if (_scene->keyboard(event->text().toStdString()[0]))
                update();
        break;
    }
}

void MyOpenGLWidget::render(const std::string& filename) {
        makeCurrent();
        _scene.reset(new Renderer(width(), height(), filename));
        doneCurrent();
        update();
}

void MyOpenGLWidget::renderAnimLBSCPU(int metric,int model){
    m_method = 0;
    m_metric = metric;
    m_model = model;
    makeCurrent();
    _scene.reset(new Renderer(width(), height(), metric, model));
    doneCurrent();
    update();
}

void MyOpenGLWidget::renderAnimLBSGPU(int metric,int model){
  m_method = 1;
  m_metric = metric;
  m_model = model;
    makeCurrent();
    _scene.reset(new RendererGPU(width(), height(), metric, model));
    doneCurrent();
    update();
}

void MyOpenGLWidget::renderAnimQuatCPU(int metric,int model){
  m_method = 2;
  m_metric = metric;
  m_model = model;
  makeCurrent();
  _scene.reset(new RendererQuat(width(), height(), metric, model));
  doneCurrent();
  update();
}

void MyOpenGLWidget::render(){
  switch(m_method){
    case 0:
      renderAnimLBSCPU(m_metric,m_model);
      break;
    case 1:
      renderAnimLBSGPU(m_metric,m_model);
      break;
    case 2:
      renderAnimQuatCPU(m_metric,m_model);
      break;
    default:
      renderAnimQuatCPU(m_metric,m_model);
      break;
    }
}
