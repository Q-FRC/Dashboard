#include "Globals.h"

#include <QStringList>

nt::NetworkTableInstance Globals::inst = nt::NetworkTableInstance::GetDefault();
ServerData Globals::server{false, "0.0.0.0", NT_DEFAULT_PORT4};

QMap<TopicTypes, QString> Globals::topicTypeDisplayNames = {
    {TopicTypes::SendableChooser, "Sendable Chooser"},
    {TopicTypes::Double, "Double"},
    {TopicTypes::String, "String"},
    {TopicTypes::Boolean, "Boolean"}
};

QMap<WidgetTypes, QString> Globals::widgetTypeDisplayNames = {
    {WidgetTypes::BooleanCheckbox, "Checkbox"},
    {WidgetTypes::BooleanDisplay, "Color Display"},
    {WidgetTypes::StringDisplay, "Text Display"},
    {WidgetTypes::DoubleDisplay, "Double Display"},
    {WidgetTypes::DoubleDial, "Dial"},
    {WidgetTypes::SendableChooser, "Sendable Chooser"},
    {WidgetTypes::CameraView, "Camera View"},
    {WidgetTypes::EnumWidget, "Enum"}
};

QStringList Globals::ntTopics{};
QMap<QString, TopicTypes> Globals::availableTopics;

bool operator==(const WidgetData &a, const WidgetData &b) {
    return (a.row == b.row) &&
           (a.col == b.col) &&
           (a.rowSpan == b.rowSpan) &&
           (a.colSpan == b.rowSpan) &&
           (a.tabIdx == b.tabIdx);
}
