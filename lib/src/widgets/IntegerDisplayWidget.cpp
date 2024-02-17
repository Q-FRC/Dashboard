#include "widgets/IntegerDisplayWidget.h"
#include "stores/TopicStore.h"

#include <QKeyEvent>
#include <QApplication>

IntegerDisplayWidget::IntegerDisplayWidget(const QString &topic, const int &defaultValue, const QString &title, const bool &ready) : TextWidget(WidgetTypes::IntegerDisplay, topic, QString::number(defaultValue), title)
{
    setTopic(topic);

    m_value = defaultValue;
    setReady(ready);
}

IntegerDisplayWidget::~IntegerDisplayWidget() {
    TopicStore::unsubscribe(m_topic.toStdString(), shared_from_this());
}

void IntegerDisplayWidget::setTopic(const QString &topic) {
    m_topic = topic;
    if (m_entry) TopicStore::unsubscribe(m_topic, shared_from_this());
    m_entry = TopicStore::subscribe(topic.toStdString(), shared_from_this(), NT_INTEGER);
}

void IntegerDisplayWidget::setValue(const nt::Value &value, QString label, bool force) {
    if (!m_text->hasFocus()) {
        m_value = value.GetInteger();
        setText(QString::number(m_value));
    }
}

void IntegerDisplayWidget::keyPressEvent(QKeyEvent *event) {
    if (m_text->hasFocus()) {
        if (m_entry) m_entry->SetInteger(m_text->text().toInt());
        m_value = m_text->text().toInt();
    }
}

