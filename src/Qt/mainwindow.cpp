#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QMessageBox>
#include <QFileDialog>
#include <QSurfaceFormat>
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
    m_metric = 0;
    m_method = 0;
    m_model = 0;
}

MainWindow::~MainWindow() {
    delete ui;
}


void MainWindow::on_actionOpen_triggered()
{
    QFileDialog fd;
    fd.open();
    QString filename = fd.getOpenFileName(this,tr("Select your .obj file"), tr("../DataFiles"), tr("OBJ files *.obj;; PLY files *.ply"));
    std::cout << "Selected file is " << filename.toStdString() << std::endl;
    ui->openglWidget->render(filename.toStdString());
}

void MainWindow::startRender(){
  switch(m_method){
    case 0:
      ui->openglWidget->renderAnimLBSCPU(m_metric,m_model);
      break;
    case 1:
      ui->openglWidget->renderAnimLBSGPU(m_metric,m_model);
      break;
    case 2:
      ui->openglWidget->renderAnimQuatCPU(m_metric,m_model);
      break;
    default:
      ui->openglWidget->renderAnimQuatCPU(m_metric,m_model);
      break;
    }
}

void MainWindow::on_actionLBS_CPU_triggered()
{
    m_method = 0;
    startRender();
}

void MainWindow::on_actionLBS_GPU_triggered()
{
    m_method = 1;
    startRender();
}

void MainWindow::on_actionDQS_CPU_triggered()
{
    m_method = 2;
    startRender();
}

void MainWindow::on_actionEuclide_triggered()
{
    m_metric = 0;
    startRender();
}

void MainWindow::on_actionRadialClosed_triggered()
{
    m_metric = 1;
    startRender();
}

void MainWindow::on_actionCylinder_triggered()
{
    m_model = 0;
    startRender();
}

void MainWindow::on_actionPatrick_triggered()
{
    m_model = 1;
    startRender();
}
