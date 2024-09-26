#ifndef CAMERASTORE_H
#define CAMERASTORE_H

#include <QObject>
#include <QUrl>
#include "networktables/NetworkTable.h"

typedef struct Camera
{
public:
    static struct Camera fromTable(std::shared_ptr<nt::NetworkTable> table);

    QUrl url;
    QString name;
    QString source;
} Camera;

class CameraStore : public QObject
{
    Q_OBJECT
private:
public:
    CameraStore();

    static QList<Camera> Cameras;
    static void filterCameras();
    static Camera getCameraFromName(QString name);

signals:
};

#endif // CAMERASTORE_H
