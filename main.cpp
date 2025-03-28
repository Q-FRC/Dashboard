#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QQmlContext>
#include <QQuickStyle>
#include <TabListModel.h>

#include "AccentsListModel.h"
#include "BuildConfig.h"
#include "ConnManager.h"
#include "Flags.h"
#include "Globals.h"
#include "NotificationHelper.h"
#include "PlatformHelper.h"
#include "TopicListModel.h"
#include "TopicStore.h"

#include <QTimer>

int main(int argc, char *argv[])
{
    QGuiApplication app(argc, argv);

    app.setOrganizationName(BuildConfig.ORG_NAME);
    app.setApplicationName(BuildConfig.APP_NAME);
    app.setApplicationVersion(BuildConfig.versionString());

    app.setWindowIcon(QIcon(":/" + BuildConfig.APP_NAME));
    app.setDesktopFileName("" + BuildConfig.APP_NAME);

    QQuickStyle::setStyle("Material");

    TopicStore store(&app);

    TopicListModel *topics = new TopicListModel(store, &app);

    SettingsManager *settings = new SettingsManager(&app);

    TabListModel *tlm = new TabListModel(settings, &app);

    ConnManager *conn = new ConnManager(&app);

    AccentsListModel *accents = new AccentsListModel(&app);
    accents->load();

    PlatformHelper *platform = new PlatformHelper(&app);

    NotificationHelper *notification = new NotificationHelper(&app);

    Globals::inst.AddConnectionListener(true, [topics, &store, conn](const nt::Event &event) {
        bool connected = event.Is(nt::EventFlags::kConnected);

        store.connect(connected);

        auto connInfo = event.GetConnectionInfo();

        qDebug() << "Connected State:" << connected;
        // qDebug() << "Log Message:" << event.GetLogMessage()->message;
        qDebug() << "Remote Info: IP" << connInfo->remote_ip << "ID" << connInfo->remote_id << "Protocol Version" << connInfo->protocol_version;
        qDebug() << "Client Ready";

        if (!connected) {
            QMetaObject::invokeMethod(topics, &TopicListModel::clear);
        } else {
            conn->setAddress(QString::fromStdString(event.GetConnectionInfo()->remote_ip));
        }
        conn->setConnected(connected);
    });

    Globals::inst.StartClient4(BuildConfig.APP_NAME.toStdString());
    Globals::inst.StartDSClient(NT_DEFAULT_PORT4);

    Globals::inst.AddListener({{""}}, nt::EventFlags::kTopic, [topics](const nt::Event &event) {
        std::string topicName(event.GetTopicInfo()->name);

        if (event.Is(nt::EventFlags::kPublish)) {
            QMetaObject::invokeMethod(topics, [topics, topicName] {
                topics->add(QString::fromStdString(topicName));
            });

        } else if (event.Is(nt::EventFlags::kUnpublish)) {
            // TODO: handle unpublishing
            // topics->remove(QString::fromStdString(topicName));
        }
    });

    nt::NetworkTableEntry tabEntry = Globals::inst.GetEntry("/QFRCDashboard/Tab");
    Globals::inst.AddListener(tabEntry, nt::EventFlags::kValueAll, [tlm](const nt::Event &event) {
        std::string_view value = event.GetValueEventData()->value.GetString();
        QString qvalue = QString::fromStdString(std::string{value});

        QMetaObject::invokeMethod(tlm, [tlm, qvalue] { tlm->selectTab(qvalue); });
    });

    nt::NetworkTableEntry notificationEntry = Globals::inst.GetEntry(
        "/QFRCDashboard/RobotNotifications");
    Globals::inst.AddListener(notificationEntry,
                              nt::EventFlags::kValueAll,
                              [tlm, &app, notification](const nt::Event &event) {
                                  std::string_view value = event.GetValueEventData()
                                                               ->value.GetString();
                                  QString qvalue = QString::fromStdString(std::string{value});
                                  QJsonDocument doc = QJsonDocument::fromJson(qvalue.toUtf8());

                                  QMetaObject::invokeMethod(notification, [doc, notification] {
                                      notification->fromJson(doc);
                                  });
                              });

    qmlRegisterUncreatableMetaObject(
        QFDFlags::staticMetaObject,
        "QFDFlags",
        1,
        0,
        "QFDFlags",
        "Attempt to create uninstantiable object \"QFDFlags\" ignored");

    QQmlApplicationEngine engine;

    engine.rootContext()->setContextProperty("topics", topics);
    engine.rootContext()->setContextProperty("settings", settings);
    engine.rootContext()->setContextProperty("topicStore", &store);
    engine.rootContext()->setContextProperty("tlm", tlm);
    engine.rootContext()->setContextProperty("conn", conn);
    engine.rootContext()->setContextProperty("accents", accents);
    engine.rootContext()->setContextProperty("platformHelper", platform);
    engine.rootContext()->setContextProperty("notificationHelper", notification);
    engine.rootContext()->setContextProperty("buildConfig", &BuildConfig);
    QObject::connect(
        &engine,
        &QQmlApplicationEngine::objectCreationFailed,
        &app,
        []() { QCoreApplication::exit(-1); },
        Qt::QueuedConnection);
    engine.loadFromModule("QFRCDashboard", "Main");

    return app.exec();
}
