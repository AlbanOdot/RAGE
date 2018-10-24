#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QMessageBox>

#include <iostream>
#include <sstream>
#include <iomanip>

MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent), ui(new Ui::MainWindow) {
    QSurfaceFormat format;
    format.setVersion(4, 1);
    format.setProfile(QSurfaceFormat::CoreProfile);
    format.setDepthBufferSize(24);
    QSurfaceFormat::setDefaultFormat(format);

    ui->setupUi(this);

    ui->openglWidget->setFocus();
}

MainWindow::~MainWindow() {
    delete ui;
}

void MainWindow::on_actionHello_clear_triggered() {
    ui->openglWidget->activatedemo(0);
}

void MainWindow::on_actionHello_triangle_triggered() {
    ui->openglWidget->activatedemo(1);
}



void MainWindow::on_actionShader_ICO_Sphere_triggered(){
    ui->openglWidget->activatedemo(5);
}


void MainWindow::on_actionDisplay_geometry_triggered(){
    ui->openglWidget->activatedemo(2);
}

