/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created by: Qt User Interface Compiler version 5.11.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenu>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QToolBar>
#include "./src/Qt/myopenglwidget.h"

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QAction *action_Version_OpenGL;
    QAction *actionHello_triangle;
    QAction *actionHello_camera;
    QAction *actionHello_spheres;
    QAction *actionHello_clear;
    QAction *actionHello_ICO_spheres;
    QAction *actionHello_UV_Sphere;
    QAction *actionHello_ICO_Sphere;
    QAction *actionShader_ICO_Sphere;
    QAction *actionOpen;
    QAction *actionClose;
    QAction *actionDisplay_geometry;
    MyOpenGLWidget *openglWidget;
    QMenuBar *menuBar;
    QMenu *menuFiles;
    QToolBar *mainToolBar;
    QStatusBar *statusBar;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName(QStringLiteral("MainWindow"));
        MainWindow->resize(1644, 1233);
        action_Version_OpenGL = new QAction(MainWindow);
        action_Version_OpenGL->setObjectName(QStringLiteral("action_Version_OpenGL"));
        actionHello_triangle = new QAction(MainWindow);
        actionHello_triangle->setObjectName(QStringLiteral("actionHello_triangle"));
        actionHello_camera = new QAction(MainWindow);
        actionHello_camera->setObjectName(QStringLiteral("actionHello_camera"));
        actionHello_spheres = new QAction(MainWindow);
        actionHello_spheres->setObjectName(QStringLiteral("actionHello_spheres"));
        actionHello_clear = new QAction(MainWindow);
        actionHello_clear->setObjectName(QStringLiteral("actionHello_clear"));
        actionHello_ICO_spheres = new QAction(MainWindow);
        actionHello_ICO_spheres->setObjectName(QStringLiteral("actionHello_ICO_spheres"));
        actionHello_UV_Sphere = new QAction(MainWindow);
        actionHello_UV_Sphere->setObjectName(QStringLiteral("actionHello_UV_Sphere"));
        actionHello_ICO_Sphere = new QAction(MainWindow);
        actionHello_ICO_Sphere->setObjectName(QStringLiteral("actionHello_ICO_Sphere"));
        actionShader_ICO_Sphere = new QAction(MainWindow);
        actionShader_ICO_Sphere->setObjectName(QStringLiteral("actionShader_ICO_Sphere"));
        actionOpen = new QAction(MainWindow);
        actionOpen->setObjectName(QStringLiteral("actionOpen"));
        actionClose = new QAction(MainWindow);
        actionClose->setObjectName(QStringLiteral("actionClose"));
        actionDisplay_geometry = new QAction(MainWindow);
        actionDisplay_geometry->setObjectName(QStringLiteral("actionDisplay_geometry"));
        openglWidget = new MyOpenGLWidget(MainWindow);
        openglWidget->setObjectName(QStringLiteral("openglWidget"));
        openglWidget->setMinimumSize(QSize(800, 600));
        MainWindow->setCentralWidget(openglWidget);
        menuBar = new QMenuBar(MainWindow);
        menuBar->setObjectName(QStringLiteral("menuBar"));
        menuBar->setGeometry(QRect(0, 0, 1644, 22));
        menuFiles = new QMenu(menuBar);
        menuFiles->setObjectName(QStringLiteral("menuFiles"));
        MainWindow->setMenuBar(menuBar);
        mainToolBar = new QToolBar(MainWindow);
        mainToolBar->setObjectName(QStringLiteral("mainToolBar"));
        MainWindow->addToolBar(Qt::TopToolBarArea, mainToolBar);
        statusBar = new QStatusBar(MainWindow);
        statusBar->setObjectName(QStringLiteral("statusBar"));
        MainWindow->setStatusBar(statusBar);

        menuBar->addAction(menuFiles->menuAction());
        menuFiles->addAction(actionOpen);
        menuFiles->addAction(actionClose);

        retranslateUi(MainWindow);

        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QApplication::translate("MainWindow", "Hello OpenGL ...", nullptr));
        action_Version_OpenGL->setText(QApplication::translate("MainWindow", "&Version OpenGL", nullptr));
        actionHello_triangle->setText(QApplication::translate("MainWindow", "Hello triangle ...", nullptr));
        actionHello_camera->setText(QApplication::translate("MainWindow", "Hello camera ...", nullptr));
        actionHello_spheres->setText(QApplication::translate("MainWindow", "Hello UV spheres ...", nullptr));
        actionHello_clear->setText(QApplication::translate("MainWindow", "Hello clear ...", nullptr));
        actionHello_ICO_spheres->setText(QApplication::translate("MainWindow", "Hello ICO Sphere", nullptr));
        actionHello_UV_Sphere->setText(QApplication::translate("MainWindow", "Hello UV Sphere", nullptr));
        actionHello_ICO_Sphere->setText(QApplication::translate("MainWindow", "Hello ICO Sphere", nullptr));
        actionShader_ICO_Sphere->setText(QApplication::translate("MainWindow", "Shader ICO Sphere", nullptr));
        actionOpen->setText(QApplication::translate("MainWindow", "Open", nullptr));
        actionClose->setText(QApplication::translate("MainWindow", "Close", nullptr));
        actionDisplay_geometry->setText(QApplication::translate("MainWindow", "Display geometry", nullptr));
        menuFiles->setTitle(QApplication::translate("MainWindow", "Files", nullptr));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H