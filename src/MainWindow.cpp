#include "MainWindow.h"
#include "Globals.h"

#include "misc/NewWidgetTreeDialog.h"
#include "misc/NTSettingsDialog.h"
#include "misc/WidgetDialogGenerator.h"
#include "misc/TabMaxSizeDialog.h"

#include "stores/FilterStore.h"

#include <networktables/NetworkTableInstance.h>

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

#include <BuildConfig.h>

#include "../ui/ui_MainWindow.h"

MainWindow::MainWindow() : QMainWindow()
{
    ui = new Ui::MainWindow;
    ui->setupUi(this);

    // Initialize Shortcuts
    {
        new QShortcut(QKeySequence(Qt::Key_Control + Qt::Key_Tab), this, [this] {
            int tabIdx = ui->centralwidget->currentIndex() + 1;
            if (tabIdx == ui->centralwidget->count()) tabIdx = 0;

            ui->centralwidget->setCurrentIndex(tabIdx);
        });
    }

    update();
}

MainWindow::~MainWindow() {
    delete ui;
}

TabWidget *MainWindow::currentTab() {
    return m_tabs.at(ui->centralwidget->currentIndex());
}

/* File I/O */

QJsonDocument MainWindow::saveObject() {
    QJsonDocument doc{};
    QJsonObject topObject{};
    QJsonArray tabs{};

    for (TabWidget *tab : m_tabs) {
        QJsonObject object = tab->saveObject();
        tabs.append(object);
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

        TabWidget *tab = new TabWidget(QPoint(3,3), this);
        tab->setMouseTracking(true);

        tab->loadObject(object);
        ui->centralwidget->addTab(tab, tab->name());
        m_tabs.append(tab);
    } // tabs
}

/* Private Member Functions */
void MainWindow::makeNewWidget(WidgetTypes type) {
    if (m_tabs.length() == 0) {
        QMessageBox::StandardButton warning = QMessageBox::warning(this, "Cannot Add Widget", "You must select a tab before adding a widget.\nWould you like to add a tab now?", QMessageBox::Yes | QMessageBox::No, QMessageBox::No);
        if (warning == QMessageBox::StandardButton::Yes) {
            newTab();
        }
    } else {
        BaseWidget *widget = BaseWidget::defaultWidgetFromTopic("", type);
        WidgetData data{0, 0, 1, 1};

        beginNewWidgetDrag(widget, data);
    }
}

/* Slots */

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

void MainWindow::openDialog() {
    QFile file(QFileDialog::getOpenFileName(
        this, "Open File", QDir::homePath(), "JSON Files (*.json);;All Files (*)"));

    open(file);
}

void MainWindow::open(QFile &file) {
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
        TabWidget *tab = new TabWidget(QPoint(3, 3), this);
        tab->setMouseTracking(true);

        m_tabs.append(tab);
        ui->centralwidget->addTab(tab, tabName);
        ui->centralwidget->setCurrentWidget(tab);
        tab->setName(tabName);
    }
}

void MainWindow::closeTab() {
    if (m_tabs.empty()) return;
    int index = ui->centralwidget->currentIndex();

    QMessageBox::StandardButton close = QMessageBox::question(this, "Close Tab?", "Are you sure you want to close this tab?", QMessageBox::Yes | QMessageBox::No, QMessageBox::No);

    if (close == QMessageBox::Yes) {
        TabWidget *tab = m_tabs.at(index);
        ui->centralwidget->removeTab(index);
        m_tabs.remove(index);
        delete tab;
    }
}

void MainWindow::renameTab() {
    if (m_tabs.empty()) return;

    bool ok;
    QString tabName = QInputDialog::getText(this, "Tab Name", "Input new tab name", QLineEdit::Normal, ui->centralwidget->tabText(ui->centralwidget->currentIndex()), &ok);

    if (!tabName.isEmpty() && ok) {
        ui->centralwidget->setTabText(ui->centralwidget->currentIndex(), tabName);
        currentTab()->setName(tabName);
    }
}

void MainWindow::setMaxSize() {
    if (m_tabs.empty()) return;

    TabWidget *tab = currentTab();
    TabMaxSizeDialog *dialog = new TabMaxSizeDialog(this, tab->maxSize());
    dialog->show();

    connect(dialog, &TabMaxSizeDialog::dataReady, this, [this, tab](QPoint point) {
        tab->setMaxSize(point);
    });
}

// New Widget
void MainWindow::newWidgetPopup() {

    if (m_tabs.length() == 0) {
        QMessageBox::StandardButton warning = QMessageBox::warning(this, "Cannot Add Widget", "You must select a tab before adding a widget.\nWould you like to add a tab now?", QMessageBox::Yes | QMessageBox::No, QMessageBox::No);
        if (warning == QMessageBox::StandardButton::Yes) {
            newTab();
        }
    } else {
        NewWidgetTreeDialog *listDialog = new NewWidgetTreeDialog(false, this);
        listDialog->setWindowTitle("Select Widget...");
        listDialog->constructList(FilterStore::FilteredTopics);

        // Width: 1/2 of available space
        // Height: 1/2 of available space
        QRect screenSize = qApp->primaryScreen()->geometry();
        listDialog->resize(screenSize.width() / 2., screenSize.height() / 2.);

        connect(listDialog, &NewWidgetTreeDialog::widgetReady, this, &MainWindow::beginNewWidgetDrag, Qt::SingleShotConnection);

        listDialog->show();
    }
}

void MainWindow::configNewWidget(BaseWidget *widget, WidgetData data) {
    WidgetDialogGenerator *dialog = new WidgetDialogGenerator(widget, this, false, data);
    dialog->setWindowTitle("New Widget");
    dialog->show();

    connect(dialog, &WidgetDialogGenerator::widgetReady, currentTab(), &TabWidget::addWidget);
    connect(dialog, &WidgetDialogGenerator::cancelled, currentTab(), &TabWidget::deleteWidget);
}

void MainWindow::beginNewWidgetDrag(BaseWidget *widget, WidgetData data) {
    TabWidget *tab = currentTab();

    tab->setDragData(widget, data);
    tab->dragStart(QCursor::pos(), QPoint(0, 0));

    // ensure connection only occurs once
    connect(tab, &TabWidget::dragDone, this, &MainWindow::configNewWidget, Qt::SingleShotConnection);
}

void MainWindow::newCameraView() {
    makeNewWidget(WidgetTypes::CameraView);
}

void MainWindow::newGraph() {
    makeNewWidget(WidgetTypes::Graph);
}

//  Menu
void MainWindow::about() {
    QStringList aboutString;
    aboutString << "Current Version: " + BuildConfig.versionString()
                << "Build Platform: " + BuildConfig.BUILD_PLATFORM
                << "Build Date: " + BuildConfig.BUILD_DATE
                << "Git Repo: " + BuildConfig.GIT_REPO
                << "Author: Carson Rueter <swurl@swurl.xyz>"
                << "Contributors: Ashley Hawkins"
                << "Copyleft 2023-2024 Carson Rueter"
                << "Enjoy :)";
    QMessageBox::about(this, "About " + BuildConfig.APP_NAME, aboutString.join("\n"));
}

void MainWindow::aboutQt() {
    QMessageBox::aboutQt(this, "About Qt");
}
