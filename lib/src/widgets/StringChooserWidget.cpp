#include "widgets/StringChooserWidget.h"
#include "Globals.h"
#include "stores/TopicStore.h"

#include <QApplication>

StringChooserWidget::StringChooserWidget(const QString &topic, const QString &defaultValue, const QString &title) : BaseWidget(WidgetTypes::SendableChooser, title, topic, true)
{
    setTopic(topic);

    m_chooser = new QComboBox(this);
    m_layout->addWidget(m_chooser, 1, 0);

    m_layout->setColumnStretch(0, -1);
    setReady(true);
}

StringChooserWidget::~StringChooserWidget() {
    TopicStore::unsubscribe(m_active, shared_from_this());
    TopicStore::unsubscribe(m_default, shared_from_this());
    TopicStore::unsubscribe(m_choices, shared_from_this());
    TopicStore::unsubscribe(m_selected, shared_from_this());
}

void StringChooserWidget::setTopic(const QString &topic) {
    m_topic = topic;

    if (m_active != nullptr) TopicStore::unsubscribe(topic.toStdString() + "/active", shared_from_this());
    if (m_default != nullptr) TopicStore::unsubscribe(topic.toStdString() + "/default", shared_from_this());
    if (m_choices != nullptr) TopicStore::unsubscribe(topic.toStdString() + "/options", shared_from_this());
    if (m_selected != nullptr) TopicStore::unsubscribe(topic.toStdString() + "/selected", shared_from_this());

    m_active = TopicStore::subscribe(topic.toStdString() + "/active", shared_from_this(), NT_STRING, "Active");
    m_default = TopicStore::subscribe(topic.toStdString() + "/default", shared_from_this(), NT_STRING, "Default", true);
    m_choices = TopicStore::subscribe(topic.toStdString() + "/options", shared_from_this(), NT_STRING_ARRAY, "Choices");
    m_selected = TopicStore::subscribe(topic.toStdString() + "/selected", shared_from_this(), NT_STRING, "Selected", true);
}

void StringChooserWidget::setValue(const nt::Value &value, QString label, bool force) {
    qDebug() << label;
    if (force) {
        QMap<std::string, QString> map{};
        map.insert("/active", "Active");
        map.insert("/options", "Choices");

        QMapIterator iter(map);
        while (iter.hasNext()) {
            iter.next();
            TopicStore::updateTopic(m_topic.toStdString() + iter.key(), shared_from_this(), iter.value());
        }

        return;
    }

    if (label == "Active") {
        QString activeValue = m_chooser->currentText();
        std::string activeValueStd = activeValue.toStdString();

        if (m_active->GetString(activeValueStd) != activeValueStd) {
            if (m_flashCounter == 5) {
                setStyleSheet("background-color: red;");
            }

            if (m_flashCounter == 10) {
                setStyleSheet("BaseWidget { background-color: " + qApp->palette().color(QPalette::ColorRole::Base).darker(150).name() + "; border: 1px solid white; color: white; }");
                m_flashCounter = -1;
            }

            ++m_flashCounter;
        } else {
            setStyleSheet("BaseWidget { background-color: " + qApp->palette().color(QPalette::ColorRole::Base).darker(150).name() + "; border: 1px solid white; color: white; }");
        }
    }

    // this is an interesting way to do things
    if (label == "Choices") {
        qDebug() << "hereewgo";
        std::vector<std::string> choices = m_choices->GetStringArray({});

        std::vector<std::string> currentChoices{};

        for (int i = 0; i < m_chooser->count(); ++i) {
            currentChoices.push_back(m_chooser->itemText(i).toStdString());
        }

        std::sort(choices.begin(), choices.end());
        std::sort(currentChoices.begin(), currentChoices.end());

        if (choices != currentChoices) {
            m_chooser->clear();

            QStringList qchoices{};

            for (const std::string &choice : choices) {
                qchoices << QString::fromStdString(choice);
            }
            m_chooser->addItems(qchoices);
            m_chooser->setCurrentText(m_value);
        }
    }
}
