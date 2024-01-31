/********************************************************************************
** Form generated from reading UI file 'MainWindow.ui'
**
** Created by: Qt User Interface Compiler version 6.6.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenu>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QTabWidget>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QAction *actionSave;
    QAction *actionSave_As;
    QAction *actionOpen;
    QAction *actionClose_Tab;
    QAction *actionNew_Tab;
    QAction *actionRename_Tab;
    QAction *actionResize_Tab;
    QAction *actionNew_NT_Widget;
    QAction *actionAbout;
    QAction *actionAbout_Qt;
    QAction *actionNew_Graph;
    QAction *actionNew_Camera_View;
    QAction *actionAdd_Camera;
    QAction *action_Preferences;
    QAction *action_NT_Server;
    QTabWidget *centralwidget;
    QMenuBar *menuBar;
    QMenu *menuFile;
    QMenu *menuRecent_Files;
    QMenu *menu_Tab;
    QMenu *menuWidget;
    QMenu *menuAbout;
    QMenu *menu_CameraServer;
    QMenu *menuSettings;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName("MainWindow");
        MainWindow->resize(800, 600);
        MainWindow->setMouseTracking(true);
        actionSave = new QAction(MainWindow);
        actionSave->setObjectName("actionSave");
        actionSave_As = new QAction(MainWindow);
        actionSave_As->setObjectName("actionSave_As");
        actionOpen = new QAction(MainWindow);
        actionOpen->setObjectName("actionOpen");
        actionClose_Tab = new QAction(MainWindow);
        actionClose_Tab->setObjectName("actionClose_Tab");
        actionNew_Tab = new QAction(MainWindow);
        actionNew_Tab->setObjectName("actionNew_Tab");
        actionRename_Tab = new QAction(MainWindow);
        actionRename_Tab->setObjectName("actionRename_Tab");
        actionResize_Tab = new QAction(MainWindow);
        actionResize_Tab->setObjectName("actionResize_Tab");
        actionNew_NT_Widget = new QAction(MainWindow);
        actionNew_NT_Widget->setObjectName("actionNew_NT_Widget");
        actionAbout = new QAction(MainWindow);
        actionAbout->setObjectName("actionAbout");
        actionAbout_Qt = new QAction(MainWindow);
        actionAbout_Qt->setObjectName("actionAbout_Qt");
        actionNew_Graph = new QAction(MainWindow);
        actionNew_Graph->setObjectName("actionNew_Graph");
        actionNew_Camera_View = new QAction(MainWindow);
        actionNew_Camera_View->setObjectName("actionNew_Camera_View");
        actionAdd_Camera = new QAction(MainWindow);
        actionAdd_Camera->setObjectName("actionAdd_Camera");
        action_Preferences = new QAction(MainWindow);
        action_Preferences->setObjectName("action_Preferences");
        action_NT_Server = new QAction(MainWindow);
        action_NT_Server->setObjectName("action_NT_Server");
        centralwidget = new QTabWidget(MainWindow);
        centralwidget->setObjectName("centralwidget");
        centralwidget->setMouseTracking(true);
        centralwidget->setMovable(true);
        MainWindow->setCentralWidget(centralwidget);
        menuBar = new QMenuBar(MainWindow);
        menuBar->setObjectName("menuBar");
        menuBar->setGeometry(QRect(0, 0, 800, 22));
        menuFile = new QMenu(menuBar);
        menuFile->setObjectName("menuFile");
        menuRecent_Files = new QMenu(menuFile);
        menuRecent_Files->setObjectName("menuRecent_Files");
        menu_Tab = new QMenu(menuBar);
        menu_Tab->setObjectName("menu_Tab");
        menuWidget = new QMenu(menuBar);
        menuWidget->setObjectName("menuWidget");
        menuAbout = new QMenu(menuBar);
        menuAbout->setObjectName("menuAbout");
        menu_CameraServer = new QMenu(menuBar);
        menu_CameraServer->setObjectName("menu_CameraServer");
        menuSettings = new QMenu(menuBar);
        menuSettings->setObjectName("menuSettings");
        MainWindow->setMenuBar(menuBar);

        menuBar->addAction(menuSettings->menuAction());
        menuBar->addAction(menuFile->menuAction());
        menuBar->addAction(menu_Tab->menuAction());
        menuBar->addAction(menuWidget->menuAction());
        menuBar->addAction(menuAbout->menuAction());
        menuBar->addAction(menu_CameraServer->menuAction());
        menuFile->addAction(actionSave);
        menuFile->addAction(actionSave_As);
        menuFile->addAction(actionOpen);
        menuFile->addAction(menuRecent_Files->menuAction());
        menu_Tab->addAction(actionClose_Tab);
        menu_Tab->addAction(actionNew_Tab);
        menu_Tab->addAction(actionRename_Tab);
        menu_Tab->addAction(actionResize_Tab);
        menuWidget->addAction(actionNew_NT_Widget);
        menuWidget->addAction(actionNew_Graph);
        menuWidget->addAction(actionNew_Camera_View);
        menuAbout->addAction(actionAbout);
        menuAbout->addAction(actionAbout_Qt);
        menu_CameraServer->addAction(actionAdd_Camera);
        menuSettings->addAction(action_Preferences);
        menuSettings->addAction(action_NT_Server);

        retranslateUi(MainWindow);
        QObject::connect(action_NT_Server, SIGNAL(triggered()), MainWindow, SLOT(ntSettingsPopup()));
        QObject::connect(actionAbout, SIGNAL(triggered()), MainWindow, SLOT(about()));
        QObject::connect(actionAbout_Qt, SIGNAL(triggered()), MainWindow, SLOT(aboutQt()));
        QObject::connect(actionClose_Tab, SIGNAL(triggered()), MainWindow, SLOT(closeTab()));
        QObject::connect(actionNew_Camera_View, SIGNAL(triggered()), MainWindow, SLOT(newCameraView()));
        QObject::connect(actionNew_Graph, SIGNAL(triggered()), MainWindow, SLOT(newGraph()));
        QObject::connect(actionNew_NT_Widget, SIGNAL(triggered()), MainWindow, SLOT(newWidgetPopup()));
        QObject::connect(actionNew_Tab, SIGNAL(triggered()), MainWindow, SLOT(newTab()));
        QObject::connect(actionOpen, SIGNAL(triggered()), MainWindow, SLOT(openDialog()));
        QObject::connect(actionRename_Tab, SIGNAL(triggered()), MainWindow, SLOT(renameTab()));
        QObject::connect(actionResize_Tab, SIGNAL(triggered()), MainWindow, SLOT(setMaxSize()));
        QObject::connect(actionSave, SIGNAL(triggered()), MainWindow, SLOT(save()));
        QObject::connect(actionSave_As, SIGNAL(triggered()), MainWindow, SLOT(saveAs()));
        QObject::connect(actionAdd_Camera, SIGNAL(triggered()), MainWindow, SLOT(cameraServerPopup()));
        QObject::connect(action_Preferences, SIGNAL(triggered()), MainWindow, SLOT(preferences()));
        QObject::connect(centralwidget, SIGNAL(currentChanged(int)), MainWindow, SLOT(forceUpdateTab(int)));

        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QCoreApplication::translate("MainWindow", "QFRCDashboard", nullptr));
        actionSave->setText(QCoreApplication::translate("MainWindow", "&Save", nullptr));
#if QT_CONFIG(shortcut)
        actionSave->setShortcut(QCoreApplication::translate("MainWindow", "Ctrl+S", nullptr));
#endif // QT_CONFIG(shortcut)
        actionSave_As->setText(QCoreApplication::translate("MainWindow", "Save &As...", nullptr));
#if QT_CONFIG(shortcut)
        actionSave_As->setShortcut(QCoreApplication::translate("MainWindow", "Ctrl+Shift+S", nullptr));
#endif // QT_CONFIG(shortcut)
        actionOpen->setText(QCoreApplication::translate("MainWindow", "&Open File...", nullptr));
#if QT_CONFIG(shortcut)
        actionOpen->setShortcut(QCoreApplication::translate("MainWindow", "Ctrl+O", nullptr));
#endif // QT_CONFIG(shortcut)
        actionClose_Tab->setText(QCoreApplication::translate("MainWindow", "&Close Tab", nullptr));
#if QT_CONFIG(shortcut)
        actionClose_Tab->setShortcut(QCoreApplication::translate("MainWindow", "Ctrl+W", nullptr));
#endif // QT_CONFIG(shortcut)
        actionNew_Tab->setText(QCoreApplication::translate("MainWindow", "&New Tab...", nullptr));
#if QT_CONFIG(shortcut)
        actionNew_Tab->setShortcut(QCoreApplication::translate("MainWindow", "Ctrl+T", nullptr));
#endif // QT_CONFIG(shortcut)
        actionRename_Tab->setText(QCoreApplication::translate("MainWindow", "&Rename Tab...", nullptr));
        actionResize_Tab->setText(QCoreApplication::translate("MainWindow", "Re&size Tab...", nullptr));
        actionNew_NT_Widget->setText(QCoreApplication::translate("MainWindow", "New &NT Widget", nullptr));
#if QT_CONFIG(shortcut)
        actionNew_NT_Widget->setShortcut(QCoreApplication::translate("MainWindow", "Ctrl+N", nullptr));
#endif // QT_CONFIG(shortcut)
        actionAbout->setText(QCoreApplication::translate("MainWindow", "&About", nullptr));
        actionAbout_Qt->setText(QCoreApplication::translate("MainWindow", "About &Qt", nullptr));
        actionNew_Graph->setText(QCoreApplication::translate("MainWindow", "New &Graph", nullptr));
#if QT_CONFIG(shortcut)
        actionNew_Graph->setShortcut(QCoreApplication::translate("MainWindow", "Ctrl+G", nullptr));
#endif // QT_CONFIG(shortcut)
        actionNew_Camera_View->setText(QCoreApplication::translate("MainWindow", "New &Camera View", nullptr));
        actionAdd_Camera->setText(QCoreApplication::translate("MainWindow", "Add &Camera...", nullptr));
        action_Preferences->setText(QCoreApplication::translate("MainWindow", "&Preferences", nullptr));
#if QT_CONFIG(shortcut)
        action_Preferences->setShortcut(QCoreApplication::translate("MainWindow", "Ctrl+,", nullptr));
#endif // QT_CONFIG(shortcut)
        action_NT_Server->setText(QCoreApplication::translate("MainWindow", "&NT Server", nullptr));
        menuFile->setTitle(QCoreApplication::translate("MainWindow", "&File", nullptr));
        menuRecent_Files->setTitle(QCoreApplication::translate("MainWindow", "&Recent Files", nullptr));
        menu_Tab->setTitle(QCoreApplication::translate("MainWindow", "&Tab", nullptr));
        menuWidget->setTitle(QCoreApplication::translate("MainWindow", "&Widget", nullptr));
        menuAbout->setTitle(QCoreApplication::translate("MainWindow", "&About", nullptr));
        menu_CameraServer->setTitle(QCoreApplication::translate("MainWindow", "&CameraServer", nullptr));
        menuSettings->setTitle(QCoreApplication::translate("MainWindow", "&Settings", nullptr));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
