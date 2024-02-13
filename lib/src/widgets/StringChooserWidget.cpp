#include "widgets/StringChooserWidget.h"
#include "Globals.h"
#include "stores/TopicStore.h"

#include <QApplication>

StringChooserWidget::StringChooserWidget(const QString &topic, const QString &defaultValue, const QString &title) : BaseWidget(WidgetTypes::SendableChooser, title, topic, true)
{
    m_value = QString::fromStdString(defaultValue.isEmpty() ? m_active->GetString("") : defaultValue.toStdString());

    m_chooser = new QComboBox(this);

    std::vector<std::string> choices = m_choices->GetStringArray({});
    QStringList qchoices{};

    for (const std::string &choice : choices) {
        qchoices << QString::fromStdString(choice);
    }
    m_chooser->addItems(qchoices);
    m_chooser->setCurrentText(m_value);

    connect(m_chooser, &QComboBox::currentTextChanged, this, [this](QString text) {
        m_selected->SetString(text.toStdString());
    });

    m_layout->addWidget(m_chooser, 1, 0);

    m_layout->setColumnStretch(0, -1);
    setReady(true);
}

StringChooserWidget::~StringChooserWidget() {
    TopicStore::unsubscribe(m_active, this);
    TopicStore::unsubscribe(m_default, this);
    TopicStore::unsubscribe(m_choices, this);
    TopicStore::unsubscribe(m_selected, this);
}

void StringChooserWidget::setTopic(const QString &topic) {
    if (m_topic == topic) return;

    BaseWidget::setTopic(topic);

    if (m_topic == topic)
        return;

    if (m_active != nullptr) TopicStore::unsubscribe(m_active, this);
    if (m_default != nullptr) TopicStore::unsubscribe(m_default, this);
    if (m_choices != nullptr) TopicStore::unsubscribe(m_choices, this);
    if (m_selected != nullptr) TopicStore::unsubscribe(m_selected, this);

    m_active = TopicStore::subscribe(topic.toStdString() + "/active", this, TopicTypes::String, "Active");
    m_default = TopicStore::subscribe(topic.toStdString() + "/default", this, TopicTypes::String, "Default", true);
    m_choices = TopicStore::subscribe(topic.toStdString() + "/options", this, TopicTypes::StringArray, "Choices");
    m_selected = TopicStore::subscribe(topic.toStdString() + "/selected", this, TopicTypes::String, "Active", true);

    setValue(nt::Value());
}

void StringChooserWidget::setValue(const nt::Value &value, QString label, bool force) {
    if (label == "Active" || force) {
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
    if (label == "Choices" || force) {
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
