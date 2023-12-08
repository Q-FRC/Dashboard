#pragma once

#include "widgets/BaseWidget.h"
#include "widgets/TabWidget.h"

#include <QMainWindow>
#include <QLabel>
#include <QGridLayout>
#include <QIcon>
#include <QPixmap>
#include <QStackedLayout>
#include <QMap>
#include <QMouseEvent>
#include <QTabWidget>
#include <QListWidget>
#include <QJsonDocument>

#include "Globals.h"

class MainWindow : public QMainWindow
{
    Q_OBJECT
private:
    QTabWidget *m_centralWidget;
    QStackedLayout *m_layout;

    QToolBar *m_toolbar;
    QMenuBar *m_menubar;

    QList<TabWidget *> m_tabWidgets;

    /**
     * Widget map. Int array format is as follows:
     * - tab idx
     * - row idx
     * - column idx
     * - rowspan
     * - colspan
    */
    QMap<BaseWidget *, WidgetData> m_widgets;

    bool m_needsRelay = true;

    QString m_filename{};

    // Dragging
    QPoint m_dragStart;
    QPoint m_dragOffset;
    BaseWidget *m_draggedWidget;
    WidgetData m_draggedWidgetData;
    bool m_dragging = false;

    // Resizing
    ResizeDirection m_currentResize;
    QRect m_initialSize;
    bool m_resizing = false;

    void mousePressEvent(QMouseEvent *event);
    void mouseMoveEvent(QMouseEvent *event);
    void mouseReleaseEvent(QMouseEvent *event);
    void resizeEvent(QResizeEvent *event);

    void dragMove(QPoint point);
    void dragRelease(QPoint point);

    void resizeMove(QPoint point);
    void resizeRelease(QPoint point);

    QMap<BaseWidget *, WidgetData> widgetsForTab(int tabIdx);

    void relay();
    WidgetData getWidgetData(BaseWidget *widget);
public:
    MainWindow();
    virtual ~MainWindow();

    void update();

    // File I/O
    QJsonDocument saveObject();
    void loadObject(const QJsonDocument &doc);

    bool positionContainsWidget(WidgetData data);

public slots:
    void newWidget(BaseWidget *widget, WidgetData data);

    // NT Settings
    void ntSettingsPopup();
    void setNtSettings(ServerData data);

    // File Actions
    void save();
    void saveAs();
    void open();

    // Tab Actions
    void newTab();
    void closeTab();
    void setMaxSize();
    void renameTab();

    // New Widget
    void newWidgetPopup();

    // Camera View
    void newCameraView();

    // About Menu
    void aboutDialog();
};
