#include <QGuiApplication>
#include <QQmlApplicationEngine>

#include "widgets/include/DirectionFlags.h"

int main(int argc, char *argv[])
{
    QGuiApplication app(argc, argv);

    qmlRegisterUncreatableMetaObject(
        DirectionFlags::staticMetaObject, // meta object created by Q_NAMESPACE macro
        "DirectionFlags",                // import statement (can be any string)
        1, 0,                          // major and minor version of the import
        "DirectionFlags",                 // name in QML (does not have to match C++ name)
        "Attempt to create uninstantiable object \"DirectionFlags\" ignored"            // error in case someone tries to create a MyNamespace object
        );

    QQmlApplicationEngine engine;
    QObject::connect(
        &engine,
        &QQmlApplicationEngine::objectCreationFailed,
        &app,
        []() { QCoreApplication::exit(-1); },
        Qt::QueuedConnection);
    engine.loadFromModule("QFRCDashboard", "Main");

    return app.exec();
}
