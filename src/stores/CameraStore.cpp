#include "stores/CameraStore.h"
#include "Globals.h"

#include <QRegularExpression>

CameraStore::CameraStore()
{
    m_table = Globals::inst.GetTable("/CameraPublisher");
    Globals::inst.AddListener({{"/CameraPublisher"}}, nt::EventFlags::kTopic, [this](const nt::Event &) {
        filterCameras();
    });
}

void CameraStore::filterCameras() {
    Cameras.clear();

    for (const std::string &st : m_table->GetSubTables()) {
        std::shared_ptr<nt::NetworkTable> subtable = m_table->GetSubTable(st);

        Camera camera = Camera::fromTable(subtable);
        Cameras.append(camera);
    }
}

Camera Camera::fromTable(std::shared_ptr<nt::NetworkTable> table) {
    Camera camera{};

    camera.Name = QString::fromStdString(table->GetEntry("description").GetString(""));
    camera.Source = QString::fromStdString(table->GetEntry("source").GetString(""));

    if (camera.Name.isEmpty()) {
        std::string path{table->GetPath()};
        QString qpath = QString::fromStdString(path);
        camera.Name = qpath.split("/").last();
    }

    std::vector<std::string> streams = table->GetEntry("streams").GetStringArray({});

    for (const std::string &stream : streams) {
        static QRegularExpression re("^(mjpe?g|ip|usb):");
        QString qstream = QString::fromStdString(stream);
        qstream.replace(re, "");
        qstream.replace("/?action=stream", "/stream.mjpg?");

        camera.Urls.append(QUrl(qstream));
    }

    return camera;
}

Camera CameraStore::getCameraFromName(QString name) {
    for (const Camera &camera : Cameras) {
        if (camera.Name == name) {
            return camera;
        }
    }

    throw std::runtime_error("Camera does not exist.");
}
