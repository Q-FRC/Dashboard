#include "widgets/FieldWidget.h"

#include <QJsonArray>

double FieldWidth = 8.2296;
double FieldLength = 8.2296 * 2.;

FieldWidget::FieldWidget(const QString &title, const std::vector<double> &defaultValue, const QString &topic, bool fromSendable)
    : BaseWidget(WidgetTypes::Field, title, topic)
{
    m_value = defaultValue;

    if (fromSendable) {
        setTopic(topic + "/Robot");
    }

    // TODO: specify preset images
    m_imageLabel = new QLabel(this);
//    setImage(Globals::File{":/images/2023-field.png"});
    m_imageLabel->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);

    m_layout->addWidget(m_imageLabel, 1, 0, 3, 1, Qt::AlignHCenter);
}

FieldWidget::~FieldWidget() {}

double FieldWidget::robotWidth() {
    return m_width;
}

void FieldWidget::setRobotWidth(double width) {
    m_width = width;
}

double FieldWidget::robotLength() {
    return m_length;
}

void FieldWidget::setRobotLength(double length) {
    m_length = length;
}

Globals::File &FieldWidget::image() {
    return m_image;
}

void FieldWidget::setImage(Globals::File image) {
    m_image = image;
    QImage qimage(m_image.fileName);

    double ratio = qMin(
        (double) this->height() / qimage.height(),
        (double) this->width() / qimage.width());

    QImage scaled = qimage.scaledToWidth(ratio * qimage.width());

    m_imageLabel->setPixmap(QPixmap::fromImage(scaled));
}

//void FieldWidget::paintEvent(QPaintEvent *event) {
//    BaseWidget::paintEvent(event);
//}

void FieldWidget::setValue(const nt::Value &value) {
    m_value = decltype(m_value)(value.GetDoubleArray().begin(), value.GetDoubleArray().end());
}

QJsonObject FieldWidget::saveObject() {
    QJsonObject object = BaseWidget::saveObject();

    // TODO: fr need to do the metaobject thing
    QJsonArray valueArray{};
    for (double val : m_value) {
        valueArray.append(val);
    }
    object.insert("value", valueArray);
    object.insert("robotWidth", robotWidth());
    object.insert("robotLength", robotLength());
    object.insert("image", m_image.fileName);

    return object;
}

BaseWidget *FieldWidget::fromJson(QJsonObject obj) {
    QJsonArray array = obj.value("value").toArray({});
    std::vector<double> value;

    for (QJsonValueRef ref : array) {
        value.push_back(ref.toDouble(0.));
    }

    FieldWidget *widget = new FieldWidget(
        obj.value("title").toString(""),
        value,
        obj.value("topic").toString(""));

    widget->setRobotWidth(obj.value("robotWidth").toDouble(0.));
    widget->setRobotLength(obj.value("robotLength").toDouble(0.));
    widget->setImage(Globals::File{obj.value("image").toString(":/2023Field.png")});

    return widget;
}
