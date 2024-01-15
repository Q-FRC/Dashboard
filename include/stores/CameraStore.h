#ifndef CAMERASTORE_H
#define CAMERASTORE_H

#include <QObject>

class CameraStore : public QObject
{
    Q_OBJECT
public:
    explicit CameraStore(QObject *parent = nullptr);

signals:
};

#endif // CAMERASTORE_H
