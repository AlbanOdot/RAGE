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
    void startRender();
private slots:

    void on_actionOpen_triggered();

    void on_actionLBS_CPU_triggered();

    void on_actionLBS_GPU_triggered();

    void on_actionDQS_CPU_triggered();

    void on_actionEuclide_triggered();

    void on_actionRadialClosed_triggered();

    void on_actionCylinder_triggered();

    void on_actionPatrick_triggered();

private:
    Ui::MainWindow *ui;
    int m_metric;//0 euclide , 1 radial
    int m_model; // 0 cylinder, 1 Patrick
    int m_method; // 0 LBSCPU, 1 LBSGPU, 2DQSCPU
};

#endif // MAINWINDOW_H
