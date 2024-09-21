#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QQmlContext>
#include <TabListModel.h>

#include "BuildConfig.h"
#include "Flags.h"
#include "Globals.h"
#include "TopicListModel.h"
#include "TopicStore.h"

int main(int argc, char *argv[])
{
    QGuiApplication app(argc, argv);

    TopicStore store(&app);
    TopicListModel *topics = new TopicListModel(store, &app);
    TabListModel *tlm = new TabListModel(&app);

    Globals::inst.AddConnectionListener(true, [topics, &store] (const nt::Event &event) {
        bool connected = event.Is(nt::EventFlags::kConnected);

        store.connect(connected);

        if (!connected) {
            QMetaObject::invokeMethod(topics, &TopicListModel::clear);
        }
    });

    Globals::inst.StartClient4(BuildConfig.APP_NAME.toStdString());
    Globals::inst.SetServer(Globals::server.server.c_str(), NT_DEFAULT_PORT4);
    Globals::inst.StartDSClient();

    Globals::inst.AddListener({{""}}, nt::EventFlags::kTopic, [topics] (const nt::Event &event) {
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

    qmlRegisterUncreatableMetaObject(
        QFDFlags::staticMetaObject,
        "QFDFlags",
        1, 0,
        "QFDFlags",
        "Attempt to create uninstantiable object \"QFDFlags\" ignored"
        );

    QQmlApplicationEngine engine;

    engine.rootContext()->setContextProperty("topics", topics);
    engine.rootContext()->setContextProperty("topicStore", &store);
    engine.rootContext()->setContextProperty("tlm", tlm);
    QObject::connect(
        &engine,
        &QQmlApplicationEngine::objectCreationFailed,
        &app,
        []() { QCoreApplication::exit(-1); },
        Qt::QueuedConnection);
    engine.loadFromModule("QFRCDashboard", "Main");

    return app.exec();
}
