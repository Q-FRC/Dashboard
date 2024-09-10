#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QQmlContext>

#include "BuildConfig.h"
#include "DirectionFlags.h"
#include "Globals.h"
#include "TopicListModel.h"

int main(int argc, char *argv[])
{
    QGuiApplication app(argc, argv);

    // Globals::inst.AddConnectionListener(true, [] (const nt::Event &event) {
    //     bool connected = event.Is(nt::EventFlags::kConnected);

    //     QMetaObject::invokeMethod(window, [window, connected] {
    //         window->setWindowTitle(
    //             QString("%1 %2 (%3) - %4")
    //                 .arg(BuildConfig.APP_NAME,
    //                      BuildConfig.versionString(),
    //                      QString::fromStdString(Globals::server.server),
    //                      QString(connected ? "" : "Not ") + "Connected")
    //             );

    //         window->setConnected(connected);
    //     });
    // });

    TopicListModel *topics = new TopicListModel(&app);

    Globals::inst.StartClient4(BuildConfig.APP_NAME.toStdString());
    Globals::inst.SetServer(Globals::server.server.c_str(), NT_DEFAULT_PORT4);
    Globals::inst.StartDSClient();

    Globals::inst.AddListener({{""}}, nt::EventFlags::kTopic, [topics] (const nt::Event &event) {
        std::string topicName(event.GetTopicInfo()->name);

        if (event.Is(nt::EventFlags::kPublish)) {
            Globals::ntTopics.append(QString::fromStdString(topicName));
            topics->add(QString::fromStdString(topicName));
        } else if (event.Is(nt::EventFlags::kUnpublish)) {
            Globals::ntTopics.removeOne(QString::fromStdString(topicName));
            topics->remove(QString::fromStdString(topicName));
        }
    });

    qmlRegisterUncreatableMetaObject(
        DirectionFlags::staticMetaObject, // meta object created by Q_NAMESPACE macro
        "DirectionFlags",                // import statement (can be any string)
        1, 0,                          // major and minor version of the import
        "DirectionFlags",                 // name in QML (does not have to match C++ name)
        "Attempt to create uninstantiable object \"DirectionFlags\" ignored"            // error in case someone tries to create a MyNamespace object
        );

    QQmlApplicationEngine engine;

    engine.rootContext()->setContextProperty("topics", topics);
    QObject::connect(
        &engine,
        &QQmlApplicationEngine::objectCreationFailed,
        &app,
        []() { QCoreApplication::exit(-1); },
        Qt::QueuedConnection);
    engine.loadFromModule("QFRCDashboard", "Main");

    return app.exec();
}
