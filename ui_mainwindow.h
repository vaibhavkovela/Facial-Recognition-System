/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created by: Qt User Interface Compiler version 5.15.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QFrame>
#include <QtWidgets/QLabel>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenu>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QAction *actionVideo;
    QAction *actionWeb_Camera;
    QAction *actionImage;
    QAction *actionAdd_New;
    QWidget *centralwidget;
    QWidget *verticalLayoutWidget;
    QVBoxLayout *verticalLayout;
    QFrame *frame;
    QLabel *label;
    QMenuBar *menubar;
    QMenu *menuFace_Recognizer;
    QMenu *menuNew_Faces;
    QStatusBar *statusbar;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName(QString::fromUtf8("MainWindow"));
        MainWindow->resize(828, 607);
        MainWindow->setLayoutDirection(Qt::LeftToRight);
        actionVideo = new QAction(MainWindow);
        actionVideo->setObjectName(QString::fromUtf8("actionVideo"));
        actionWeb_Camera = new QAction(MainWindow);
        actionWeb_Camera->setObjectName(QString::fromUtf8("actionWeb_Camera"));
        actionImage = new QAction(MainWindow);
        actionImage->setObjectName(QString::fromUtf8("actionImage"));
        actionAdd_New = new QAction(MainWindow);
        actionAdd_New->setObjectName(QString::fromUtf8("actionAdd_New"));
        centralwidget = new QWidget(MainWindow);
        centralwidget->setObjectName(QString::fromUtf8("centralwidget"));
        verticalLayoutWidget = new QWidget(centralwidget);
        verticalLayoutWidget->setObjectName(QString::fromUtf8("verticalLayoutWidget"));
        verticalLayoutWidget->setGeometry(QRect(90, 80, 641, 431));
        verticalLayout = new QVBoxLayout(verticalLayoutWidget);
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        verticalLayout->setContentsMargins(0, 0, 0, 0);
        frame = new QFrame(verticalLayoutWidget);
        frame->setObjectName(QString::fromUtf8("frame"));
        frame->setFrameShape(QFrame::StyledPanel);
        frame->setFrameShadow(QFrame::Raised);
        label = new QLabel(frame);
        label->setObjectName(QString::fromUtf8("label"));
        label->setGeometry(QRect(-90, 10, 721, 491));

        verticalLayout->addWidget(frame);

        MainWindow->setCentralWidget(centralwidget);
        menubar = new QMenuBar(MainWindow);
        menubar->setObjectName(QString::fromUtf8("menubar"));
        menubar->setGeometry(QRect(0, 0, 828, 22));
        menuFace_Recognizer = new QMenu(menubar);
        menuFace_Recognizer->setObjectName(QString::fromUtf8("menuFace_Recognizer"));
        menuNew_Faces = new QMenu(menubar);
        menuNew_Faces->setObjectName(QString::fromUtf8("menuNew_Faces"));
        MainWindow->setMenuBar(menubar);
        statusbar = new QStatusBar(MainWindow);
        statusbar->setObjectName(QString::fromUtf8("statusbar"));
        MainWindow->setStatusBar(statusbar);

        menubar->addAction(menuNew_Faces->menuAction());
        menubar->addAction(menuFace_Recognizer->menuAction());
        menuFace_Recognizer->addAction(actionVideo);
        menuFace_Recognizer->addAction(actionWeb_Camera);
        menuFace_Recognizer->addAction(actionImage);
        menuFace_Recognizer->addAction(actionAdd_New);

        retranslateUi(MainWindow);

        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QCoreApplication::translate("MainWindow", "MainWindow", nullptr));
        actionVideo->setText(QCoreApplication::translate("MainWindow", "Video", nullptr));
        actionWeb_Camera->setText(QCoreApplication::translate("MainWindow", "Web Camera", nullptr));
        actionImage->setText(QCoreApplication::translate("MainWindow", "Image", nullptr));
        actionAdd_New->setText(QCoreApplication::translate("MainWindow", "Add New", nullptr));
        label->setText(QString());
        menuFace_Recognizer->setTitle(QCoreApplication::translate("MainWindow", "Select Mode", nullptr));
        menuNew_Faces->setTitle(QCoreApplication::translate("MainWindow", "Face Recognizer", nullptr));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
