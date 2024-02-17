#include "widgets/BooleanDisplayWidget.h"
#include "stores/TopicStore.h"

BooleanDisplayWidget::BooleanDisplayWidget(const QString &topic, const bool &defaultValue, const QString &title) : BaseWidget(WidgetTypes::BooleanDisplay, title, topic)
{
    setTopic(topic);

    m_value = defaultValue;
    m_colorWidget = new ShapedFrame(Globals::FrameShape::Rectangle, this);

    m_layout->addWidget(m_colorWidget, 1, 0, 3, 1);
    setReady(true);
}

BooleanDisplayWidget::~BooleanDisplayWidget() {
    TopicStore::unsubscribe(m_topic.toStdString(), shared_from_this());
}

QColor BooleanDisplayWidget::trueColor() {
    return m_trueColor;
}

void BooleanDisplayWidget::setTrueColor(const QColor &color) {
    m_trueColor = color;
}

QColor BooleanDisplayWidget::falseColor() {
    return m_falseColor;
}

void BooleanDisplayWidget::setFalseColor(const QColor &color) {
    m_falseColor = color;
}

Globals::FrameShape BooleanDisplayWidget::shape() {
    return m_shape;
}

void BooleanDisplayWidget::setShape(Globals::FrameShape shape) {
    m_shape = shape;
    m_colorWidget->setShape(shape);
}

void BooleanDisplayWidget::setTopic(const QString &topic) {


    m_topic = topic;
    if (m_entry) TopicStore::unsubscribe(m_topic, this);
    m_entry = TopicStore::subscribe(topic.toStdString(), this, NT_BOOLEAN);
}

void BooleanDisplayWidget::setValue(const nt::Value &value, QString label, bool force) {
    m_value = value.GetBoolean();

    m_colorWidget->setColor(m_value ? m_trueColor : m_falseColor);
}
