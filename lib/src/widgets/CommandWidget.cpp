#include "widgets/CommandWidget.h"
#include "Globals.h"
#include "stores/TopicStore.h"

#include <QApplication>

CommandWidget::CommandWidget(const QString &topic, const QString &title) : BaseWidget(WidgetTypes::Command, title, topic, true)
{
    setTopic(topic);

    m_button = new QPushButton(QString::fromStdString(m_name->GetString("Command")), this);

    connect(m_button, &QPushButton::clicked, this, [this](bool) {
        bool value = m_running->GetBoolean(false);
        m_running->SetBoolean(!value);
    });

    m_layout->addWidget(m_button, 1, 0, 3, 1);

    setReady(true);
}

CommandWidget::~CommandWidget() {
    TopicStore::unsubscribe(m_name, this);
    TopicStore::unsubscribe(m_running, this);
}

void CommandWidget::setTopic(const QString &topic) {
    if (m_topic == topic) return;

    m_topic = topic;

    if (m_name != nullptr) TopicStore::unsubscribe(m_name, this);
    if (m_running != nullptr) TopicStore::unsubscribe(m_running, this);

    m_name = TopicStore::subscribe(topic.toStdString() + "/.name", this, TopicTypes::String, "Name");
    m_running = TopicStore::subscribe(topic.toStdString() + "/running", this, TopicTypes::Boolean, "Running", true);
}

void CommandWidget::setValue(const nt::Value &value, QString label, bool force) {
    if (label == "Name" || force)
        m_button->setText(QString::fromStdString(std::string{value.GetString()}));
}
