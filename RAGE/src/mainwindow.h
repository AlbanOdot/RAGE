#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

namespace Ui {
    class MainWindow;
}

class MainWindow : public QMainWindow {
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private slots:
    void on_action_Version_OpenGL_triggered();

    void on_actionHello_triangle_triggered();

    void on_actionHello_camera_triggered();

    void on_actionHello_UV_Sphere_triggered();

    void on_actionHello_ICO_Sphere_triggered();

    void on_actionHello_clear_triggered();

    void on_actionShader_ICO_Sphere_triggered();

private:
    Ui::MainWindow *ui;
};

#endif // MAINWINDOW_H
