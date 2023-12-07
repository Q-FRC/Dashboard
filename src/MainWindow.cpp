#include "MainWindow.h"
#include "Globals.h"

#include "misc/NewWidgetTreeDialog.h"
#include "misc/NTSettingsDialog.h"
#include "misc/WidgetDialogGenerator.h"
#include "misc/TabMaxSizeDialog.h"

#include <ntcore/networktables/NetworkTableInstance.h>

#include <QToolBar>
#include <QMenuBar>
#include <QInputDialog>
#include <QMenu>
#include <QListWidget>
#include <QMenu>
#include <QMessageBox>
#include <QJsonArray>
#include <QFileDialog>
#include <QApplication>
#include <QMetaProperty>
#include <QShortcut>
#include <QDrag>

MainWindow::MainWindow()
{
    setCentralWidget(m_centralWidget = new QTabWidget);

    m_toolbar = new QToolBar(this);

    addToolBar(Qt::ToolBarArea::BottomToolBarArea, m_toolbar);

    m_menubar = menuBar();
    // NT Settings
    {
        QAction *ntServerAction = new QAction("NT &Server");
        connect(ntServerAction, &QAction::triggered, this, &MainWindow::ntSettingsPopup);

        m_menubar->addAction(ntServerAction);
    } // End NT Settings

    { // File
        QMenu *fileMenu = new QMenu("&File", this);

        QAction *saveAction = new QAction("Save", fileMenu);
        saveAction->setShortcut(tr("Ctrl+S"));
        fileMenu->addAction(saveAction);

        connect(saveAction, &QAction::triggered, this, &MainWindow::save);

        QAction *saveAsAction = new QAction("Save As...", fileMenu);
        saveAsAction->setShortcut(tr("Ctrl+Shift+S"));
        fileMenu->addAction(saveAsAction);

        connect(saveAsAction, &QAction::triggered, this, &MainWindow::saveAs);

        QAction *loadAction = new QAction("Open File...", fileMenu);
        loadAction->setShortcut(tr("Ctrl+O"));
        fileMenu->addAction(loadAction);

        connect(loadAction, &QAction::triggered, this, &MainWindow::open);

        m_menubar->addMenu(fileMenu);
    } // End File

    { // Tab
        QMenu *tabMenu = new QMenu("&Tab", this);

        QAction *newTab = new QAction("New Tab", tabMenu);
        newTab->setShortcut(QKeySequence::AddTab);
        connect(newTab, &QAction::triggered, this, &MainWindow::newTab);
        tabMenu->addAction(newTab);

        QAction *closeTab = new QAction("Close Tab", tabMenu);
        closeTab->setShortcut(QKeySequence::Close);
        connect(closeTab, &QAction::triggered, this, &MainWindow::closeTab);
        tabMenu->addAction(closeTab);

        QAction *resizeTab = new QAction("Resize Tab", tabMenu);
        connect(resizeTab, &QAction::triggered, this, &MainWindow::setMaxSize);
        tabMenu->addAction(resizeTab);

        QAction *renameTab = new QAction("Rename Tab", tabMenu);
        connect(renameTab, &QAction::triggered, this, &MainWindow::renameTab);
        tabMenu->addAction(renameTab);

        m_menubar->addMenu(tabMenu);
    } // End Tab

    { // New Widget
        QAction *newWidgetAction = new QAction("&New Widget", this);

        connect(newWidgetAction, &QAction::triggered, this, &MainWindow::newWidgetPopup);

        m_menubar->addAction(newWidgetAction);
    } // End New Widget

    { // Camera View
        QAction *cameraAction = new QAction("New &Camera View", this);

        connect(cameraAction, &QAction::triggered, this, &MainWindow::newCameraView);

        m_menubar->addAction(cameraAction);
    } // End Camera View

    { // About
        QMenu *aboutMenu = new QMenu("&About");

        QAction *aboutAction = new QAction("About QFRCDashboard", aboutMenu);
        connect(aboutAction, &QAction::triggered, this, &MainWindow::aboutDialog);
        aboutMenu->addAction(aboutAction);

        QAction *aboutQtAction = new QAction("About Qt", aboutMenu);
        connect(aboutQtAction, &QAction::triggered, this, [this] {
            QMessageBox::aboutQt(this, "About Qt");
        });
        aboutMenu->addAction(aboutQtAction);

        menuBar()->addMenu(aboutMenu);
    }

    // Initialize Shortcuts
    {
        new QShortcut(QKeySequence(Qt::Key_Control + Qt::Key_Tab), this, [this] {
            int tabIdx = m_centralWidget->currentIndex() + 1;
            if (tabIdx == m_centralWidget->count()) tabIdx = 0;

            m_centralWidget->setCurrentIndex(tabIdx);
        });
    }

    update();
}

MainWindow::~MainWindow() {}

void MainWindow::update() {
    QMainWindow::update();

    QMapIterator<BaseWidget *, WidgetData> iterator(m_widgets);

    while (iterator.hasNext())
    {
        iterator.next();

        iterator.key()->update();
    }
}

/* File I/O */

QJsonDocument MainWindow::saveObject() {
    QJsonDocument doc{};
    QJsonObject topObject{};
    QJsonArray tabs{};

    for (TabWidget *tab : m_tabWidgets) {
        QJsonObject object{};
        int tabIdx = m_centralWidget->indexOf(tab);

        object.insert("tabIdx", tabIdx);
        object.insert("tabName", m_centralWidget->tabText(tabIdx));

        QPoint maxSize = m_tabWidgets.at(tabIdx)->maxSize();
        object.insert("maxSize", QJsonArray{ maxSize.x(), maxSize.y() });

        QJsonArray widgets{};

        QMapIterator<BaseWidget *, WidgetData> iterator(widgetsForTab(tabIdx));

        while (iterator.hasNext()) {
            iterator.next();

            QJsonObject widgetObj = iterator.key()->saveObject();
            WidgetData data = iterator.value();

            widgetObj.insert("geometry", QJsonArray({data.row, data.col, data.rowSpan, data.colSpan}));

            widgets.insert(widgets.size(), widgetObj);
        }

        object.insert("widgets", widgets);
        tabs.insert(tabs.size(), object);
    }

    QJsonObject serverObj{};
    serverObj.insert("useTeamNumber", Globals::server.teamNumber);
    serverObj.insert("address", QString::fromStdString(Globals::server.server));
    serverObj.insert("port", Globals::server.port);

    topObject.insert("server", serverObj);
    topObject.insert("tabs", tabs);
    doc.setObject(topObject);
    return doc;
}

void MainWindow::loadObject(const QJsonDocument &doc) {
    QJsonObject object = doc.object();

    // TODO: load server

    QJsonObject serverObj = object.value("server").toObject();

    ServerData server = ServerData{
        serverObj.value("useTeamNumber").toBool(false),
        serverObj.value("address").toString("0.0.0.0").toStdString(),
        serverObj.value("port").toInt(NT_DEFAULT_PORT4)
    };

    setNtSettings(server);

    QJsonArray array = object.value("tabs").toArray();

    for (QJsonValueRef ref : array) {
        QJsonObject object = ref.toObject();

        TabWidget *tab = new TabWidget(QPoint(3,3));

        int tabIdx = object.value("tabIdx").toInt();

        m_centralWidget->insertTab(tabIdx, tab, object.value("tabName").toString());
        m_tabWidgets.insert(tabIdx, tab);

        QJsonArray maxSize = object.value("maxSize").toArray();
        tab->setMaxSize(QPoint(maxSize.at(0).toInt(3), maxSize.at(1).toInt(3)));

        QJsonArray widgets = object.value("widgets").toArray();

        for (QJsonValueRef wref : widgets) {
            QJsonObject widgetObject = wref.toObject();

            WidgetTypes type = (WidgetTypes) widgetObject.value("widgetType").toInt();
            BaseWidget *widget = BaseWidget::defaultWidgetFromTopic("", type);
            widget->setParent(this);
            WidgetData data = widget->fromJson(widgetObject, tabIdx);

            m_widgets.insert(widget, data);
        } // widgets
    } // tabs

    relay();
}

bool MainWindow::positionContainsWidget(int row, int col, int tab) {
    for (const WidgetData &data : m_widgets.values())
    {
        if (data.tabIdx == tab && (data.row <= row && row < data.row + data.rowSpan)
            && (data.col <= col && col < data.col + data.colSpan)) {
            return true;
        }
    }

    return false;
}

/* Private Member Functions */
void MainWindow::mousePressEvent(QMouseEvent *event) {
    BaseWidget *widgetPressed = nullptr;

    QMapIterator<BaseWidget *, WidgetData> iterator(m_widgets);

    while (iterator.hasNext())
    {
        iterator.next();
        BaseWidget *widget = iterator.key();
        WidgetData data = iterator.value();
        if (widget->geometry().contains(event->pos()) && data.tabIdx == m_centralWidget->currentIndex()) {
            widgetPressed = widget;
            break;
        }
    }

    if (event->button() == Qt::RightButton && widgetPressed) {
        QMenu *menu = widgetPressed->constructContextMenu(m_widgets.value(widgetPressed));

        connect(widgetPressed, &BaseWidget::reconfigRequested, this, [this, widgetPressed](BaseWidget *widget, WidgetData data) {
            data.tabIdx = m_centralWidget->currentIndex();

            m_widgets.remove(widgetPressed);
            m_widgets.insert(widget, data);

            widget->setTitle(widgetPressed->title());

            relay();
        });

        connect(widgetPressed, &BaseWidget::deleteRequested, this, [this, widgetPressed] {
            m_widgets.remove(widgetPressed);
            relay();

            delete widgetPressed;
        });

        menu->popup(event->globalPosition().toPoint());
    } else if (event->button() == Qt::LeftButton && widgetPressed) {
        m_dragStart = event->position().toPoint();
        m_draggedWidget = widgetPressed;
        m_draggedWidgetData = m_widgets.value(widgetPressed);
        m_draggedWidget->raise();

        m_dragOffset = (event->position() - widgetPressed->pos()).toPoint();
    }
}

void MainWindow::mouseMoveEvent(QMouseEvent *event) {
    if (!(event->buttons() & Qt::LeftButton) || !m_draggedWidget)
        return;
    if ((event->pos() - m_dragStart).manhattanLength()
        < QApplication::startDragDistance())
        return;

    m_draggedWidget->move(QPoint(event->position().x(), event->position().y()) - m_dragOffset);

    int tabIdx = m_centralWidget->currentIndex();
    TabWidget *tab = m_tabWidgets.at(tabIdx);

    if (!tab->hasSelection()) {
        tab->layout()->removeWidget(m_draggedWidget);
        m_widgets.remove(m_draggedWidget);
    }

    int col = std::floor(event->position().x() / (tab->width() / tab->maxSize().x()));
    int row = std::floor(event->position().y() / (tab->height() / tab->maxSize().y()));

    int colSpan = m_draggedWidgetData.colSpan;
    int rowSpan = m_draggedWidgetData.rowSpan;

    tab->setSelectedIndex(WidgetData{tabIdx, row, col, rowSpan, colSpan});

    tab->setValidSelection(!positionContainsWidget(row, col, tabIdx) &&
                           (row + rowSpan - 1 < tab->maxSize().x() && (col + colSpan - 1) < tab->maxSize().y()));
}

void MainWindow::mouseReleaseEvent(QMouseEvent *event) {
    if (m_tabWidgets.empty()) return;
    TabWidget *tab = m_tabWidgets.at(m_centralWidget->currentIndex());

    if (!tab->hasSelection()) return;

    WidgetData data;

    if (tab->isValidSelection()) {
        data = tab->selectedIndex();
    } else {
        data = m_draggedWidgetData;
    }

    m_widgets.insert(m_draggedWidget,
                     data);
    relay();
    tab->setHasSelection(false);

    m_draggedWidget = nullptr;
}

void MainWindow::resizeEvent(QResizeEvent *event) {
    QMainWindow::resizeEvent(event);
    update();
}

QMap<BaseWidget *, WidgetData> MainWindow::widgetsForTab(int tabIdx) {
    QMap<BaseWidget *, WidgetData> map{};

    QMapIterator<BaseWidget *, WidgetData> iterator(m_widgets);

    while(iterator.hasNext()) {
        iterator.next();

        if (iterator.value().tabIdx == tabIdx) {
            map.insert(iterator.key(), iterator.value());
        }
    }

    return map;
}

void MainWindow::relay() {
    QMapIterator<BaseWidget *, WidgetData> iterator(m_widgets);

    while (iterator.hasNext())
    {
        iterator.next();

        WidgetData data = iterator.value();
        TabWidget *tabWidget = m_tabWidgets.at(data.tabIdx);

        if (tabWidget != nullptr) {
            tabWidget->layout()->removeWidget(iterator.key());
            tabWidget->layout()->addWidget(iterator.key(), data.row, data.col, data.rowSpan, data.colSpan);
        }
    }

    update();
}

/* Slots */
void MainWindow::newWidget(BaseWidget *widget, WidgetData data) {
    data.tabIdx = m_centralWidget->currentIndex();
    m_widgets.insert(widget, data);
    relay();
}

// NT Settings
void MainWindow::ntSettingsPopup() {
    NTSettingsDialog *dialog = new NTSettingsDialog(this);

    dialog->show();

    connect(dialog, &NTSettingsDialog::dataReady, this, &MainWindow::setNtSettings);
}

void MainWindow::setNtSettings(ServerData data) {
    std::string server = data.server;
    bool isTeamNumber = data.teamNumber;
    int port = data.port;

    if (server.empty()) return;

    if (isTeamNumber) {
        int team;
        try {
            team = std::stoi(server);
        } catch (std::invalid_argument const &) {
            QMessageBox::critical(this, "Malformed Input", "Team number was selected but address does not resemble an integer.");
            return;
        }

        Globals::inst.SetServerTeam(team, port);
    } else {
        Globals::inst.SetServer(server.c_str(), port);
    }

    Globals::server = data;
    Globals::inst.Disconnect();
}

// File Actions
void MainWindow::save() {
    if (m_filename.isEmpty()) {
        return saveAs();
    }

    QFile file(m_filename);

    if (!file.open(QIODevice::WriteOnly | QIODevice::Text)) {
        QMessageBox::critical(this, "Save Failed!", "Failed to open file for writing. "
                                                    "Directory may not exist or may be read-only.",
                              QMessageBox::StandardButton::Ok);
        return;
    }

    QTextStream stream(&file);
    stream << saveObject().toJson();
    file.close();
}

void MainWindow::saveAs() {
    QFile file(QFileDialog::getSaveFileName(
        this, "Save File", QDir::homePath(), "JSON Files (*.json);;All Files (*)"));

    if (!file.open(QIODevice::WriteOnly | QIODevice::Text)) {
        QMessageBox::critical(this, "Save Failed!", "Failed to open file for writing. "
                                                    "Directory may not exist or may be read-only.",
                              QMessageBox::StandardButton::Ok);
        return;
    }

    m_filename = file.fileName();

    QTextStream stream(&file);
    stream << saveObject().toJson();
    file.close();
}

void MainWindow::open() {
    QFile file(QFileDialog::getOpenFileName(
        this, "Open File", QDir::homePath(), "JSON Files (*.json);;All Files (*)"));

    if (!file.open(QIODevice::ReadOnly | QIODevice::Text)) {
        QMessageBox::critical(this, "Load Failed!", "Failed to open file for reading. "
                                                    "Directory may not exist or may be inaccessible.",
                              QMessageBox::StandardButton::Ok);
        return;
    }

    m_filename = file.fileName();

    QTextStream stream(&file);
    QByteArray data = stream.readAll().toUtf8();

    QJsonDocument doc = QJsonDocument::fromJson(data);

    loadObject(doc);
    file.close();
}

// Tab Actions
void MainWindow::newTab() {
    bool ok;
    QString tabName = QInputDialog::getText(this, "New Tab Name", "Input new tab name", QLineEdit::Normal, "", &ok);

    if (!tabName.isEmpty() && ok) {
        TabWidget *tab = new TabWidget(QPoint(3, 3));

        m_tabWidgets.append(tab);
        m_centralWidget->addTab(tab, tabName);
        m_centralWidget->setCurrentWidget(tab);
    }
}

void MainWindow::closeTab() {
    int index = m_centralWidget->currentIndex();

    QMessageBox::StandardButton close = QMessageBox::question(this, "Close Tab?", "Are you sure you want to close this tab?", QMessageBox::Yes | QMessageBox::No, QMessageBox::No);

    if (close == QMessageBox::Yes) {
        QWidget *tab = m_centralWidget->widget(index);
        m_centralWidget->removeTab(index);
        m_tabWidgets.remove(index);

        QMapIterator<BaseWidget *, WidgetData> iterator(m_widgets);

        while (iterator.hasNext())
        {
            iterator.next();
            BaseWidget *widget = iterator.key();
            WidgetData data = iterator.value();

            if (data.tabIdx == index) {
                m_widgets.remove(widget);
                delete widget;
            } else if (data.tabIdx > index) {
                data.tabIdx -= 1;

                m_widgets.remove(widget);
                m_widgets.insert(widget, data);
            }
        }
    }
    relay();
}

void MainWindow::renameTab() {
    bool ok;
    QString tabName = QInputDialog::getText(this, "Tab Name", "Input new tab name", QLineEdit::Normal, m_centralWidget->tabText(m_centralWidget->currentIndex()), &ok);

    if (!tabName.isEmpty() && ok) {
        m_centralWidget->setTabText(m_centralWidget->currentIndex(), tabName);
    }
}

void MainWindow::setMaxSize() {
    TabWidget *tab = m_tabWidgets.at(m_centralWidget->currentIndex());
    TabMaxSizeDialog *dialog = new TabMaxSizeDialog(this, tab->maxSize());
    dialog->show();

    connect(dialog, &TabMaxSizeDialog::dataReady, this, [this, tab](QPoint point) {
        tab->setMaxSize(point);
    });
}

// New Widget
void MainWindow::newWidgetPopup() {

    if (m_tabWidgets.length() == 0) {
        QMessageBox::StandardButton warning = QMessageBox::warning(this, "Cannot Add Widget", "You must select a tab before adding a widget.\nWould you like to add a tab now?", QMessageBox::Yes | QMessageBox::No, QMessageBox::No);
        if (warning == QMessageBox::StandardButton::Yes) {
            newTab();
        }
    } else {
        NewWidgetTreeDialog *listDialog = new NewWidgetTreeDialog(this);
        listDialog->setWindowTitle("Select Widget...");

        // Width: 1/2 of available space
        // Height: 1/2 of available space
        QRect screenSize = qApp->primaryScreen()->geometry();
        listDialog->resize(screenSize.width() / 2., screenSize.height() / 2.);

        connect(listDialog, &NewWidgetTreeDialog::widgetReady, this, &MainWindow::newWidget);
        listDialog->show();
    }
}

// Camera View
void MainWindow::newCameraView() {
    if (m_tabWidgets.length() == 0) {
        QMessageBox::StandardButton warning = QMessageBox::warning(this, "Cannot Add Widget", "You must select a tab before adding a widget.\nWould you like to add a tab now?", QMessageBox::Yes | QMessageBox::No, QMessageBox::No);
        if (warning == QMessageBox::StandardButton::Yes) {
            newTab();
        }
    } else {
        BaseWidget *widget = BaseWidget::defaultWidgetFromTopic("", WidgetTypes::CameraView);
        widget->setParent(this);
        WidgetDialogGenerator *dialog = new WidgetDialogGenerator(widget, this);
        dialog->setWindowTitle("New Camera View");
        dialog->open();

        connect(dialog, &WidgetDialogGenerator::widgetReady, this, &MainWindow::newWidget);
    }
}

//  Menu
void MainWindow::aboutDialog() {
    QStringList aboutString;
    aboutString << "Current Version: 1.0.0-beta3"
                << "GitHub: https://github.com/binex-dsk/QFRCDashboard"
                << "Author: Carson Rueter <swurl@swurl.xyz>"
                << "Contributors: Ashley Hawkins"
                << "Copyleft 2023 Carson Rueter"
                << "Enjoy :)";
    QMessageBox::about(this, "About QFRCDashboard", aboutString.join("\n"));
}
