#pragma once

// #include "CentralWidget.h"

#include "widgets/BaseWidget.h"
#include "widgets/TabWidget.h"

#include <QMainWindow>
#include <QLabel>
#include <QGridLayout>
#include <QMap>
#include <QMouseEvent>
#include <QJsonDocument>
#include <QTabWidget>

#include "Globals.h"

QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT
private:
    QList<TabWidget *> m_tabs;

    QString m_filename{};

    void makeNewWidget(WidgetTypes type);

    Ui::MainWindow *ui;
public:
    MainWindow();
    virtual ~MainWindow();

    TabWidget *currentTab();

    // File I/O
    QJsonDocument saveObject();
    void loadObject(const QJsonDocument &doc);

public slots:
    // NT Settings
    void ntSettingsPopup();
    void setNtSettings(ServerData data);

    // File Actions
    void save();
    void saveAs();
    void openDialog();
    void open(QFile &file);

    // Tab Actions
    void newTab();
    void closeTab();
    void setMaxSize();
    void renameTab();

    // New Widget
    void newWidgetPopup();
    void configNewWidget(BaseWidget *widget, WidgetData data);
    void beginNewWidgetDrag(BaseWidget *widget, WidgetData data);
    void newCameraView();
    void newGraph();

    // About Menu
    void about();
    void aboutQt();
};
