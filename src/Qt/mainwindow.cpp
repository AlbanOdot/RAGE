#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QMessageBox>
#include <QFileDialog>
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


void MainWindow::on_actionOpen_triggered()
{
    QFileDialog fd;
    fd.open();
    QString filename = fd.getOpenFileName(this,tr("Select your .obj file"), tr("../DataFiles"), tr("ALL files *.*;;OBJ files *.obj;; PLY files *.ply;;STL files *.stl"));
    std::cout << "Selected file is " << filename.toStdString() << std::endl;
    ui->openglWidget->render(filename.toStdString());
}


void MainWindow::on_actionAnimation_triggered()
{
    //0 = cylinder;
    ui->openglWidget->render(0);
}
