#include "widgets/FMSInfoWidget.h"

#include "stores/TopicStore.h"

QMap<MatchType, QString> MatchTypeNames = {
    {MatchType::Elimination, "Elimination"},
    {MatchType::None, "None"},
    {MatchType::Practice, "Practice"},
    {MatchType::Qualification, "Qual"}
};

QMap<AllianceStation, QString> StationNames = {
    {AllianceStation::Invalid, "None"},
    {AllianceStation::Red1, "Red 1"},
    {AllianceStation::Red2, "Red 2"},
    {AllianceStation::Red3, "Red 3"},
    {AllianceStation::Blue1, "Blue 1"},
    {AllianceStation::Blue2, "Blue 2"},
    {AllianceStation::Blue3, "Blue 3"}
};

FMSInfoWidget::FMSInfoWidget(const QString &table, const QString &title)
    : BaseWidget(WidgetTypes::FMSInfo, title, table, true)
{
    m_event = TopicStore::subscribe(table.toStdString() + "/EventName", this);
    m_controlWord = TopicStore::subscribe(table.toStdString() + "/FMSControlData", this);
    m_gameSpecificMessage = TopicStore::subscribe(table.toStdString() + "/GameSpecificMessage", this);
    m_redAlliance = TopicStore::subscribe(table.toStdString() + "/IsRedAlliance", this);
    m_matchNumber = TopicStore::subscribe(table.toStdString() + "/MatchNumber", this);
    m_matchType = TopicStore::subscribe(table.toStdString() + "/MatchType", this);
    m_allianceStation = TopicStore::subscribe(table.toStdString() + "/StationNumber", this);

    m_matchLabel = new QLabel("Match: Unknown", this);
    m_stationLabel = new QLabel("Station: Unknown", this);
    m_eventLabel = new QLabel("Event: Unknown", this);
    m_gsmLabel = new QLabel("Game Specific Message:\nUnknown", this);

    m_dsIconLabel = new QLabel(this);
    m_dsLabel = new QLabel("DS Disconnected", this);

    m_fmsIconLabel = new QLabel(this);
    m_fmsLabel = new QLabel("FMS Disconnected", this);

    m_controlLabel = new QLabel("Robot State: Unknown", this);

    m_layout->addWidget(m_title, 0, 0, 1, 2);

    m_layout->addWidget(m_matchLabel, 1, 0, 1, 2, Qt::AlignHCenter | Qt::AlignTop);
    m_layout->addWidget(m_stationLabel, 2, 0, 1, 2, Qt::AlignHCenter | Qt::AlignTop);
    m_layout->addWidget(m_eventLabel, 3, 0, 1, 2, Qt::AlignHCenter | Qt::AlignTop);
    m_layout->addWidget(m_gsmLabel, 4, 0, 1, 2, Qt::AlignHCenter | Qt::AlignTop);

    m_layout->addWidget(m_dsIconLabel, 5, 0, Qt::AlignRight | Qt::AlignTop);
    m_layout->addWidget(m_dsLabel, 5, 1, Qt::AlignLeft | Qt::AlignTop);

    m_layout->addWidget(m_fmsIconLabel, 6, 0, Qt::AlignRight | Qt::AlignTop);
    m_layout->addWidget(m_fmsLabel, 6, 1, Qt::AlignLeft | Qt::AlignTop);

    m_layout->addWidget(m_controlLabel, 7, 0, 1, 2, Qt::AlignCenter);

    m_layout->setColumnStretch(0, 6);
    m_layout->setColumnStretch(1, 11);

    qDebug() << m_event->Exists();
}

FMSInfoWidget::~FMSInfoWidget() {
    TopicStore::unsubscribe(m_topic.toStdString(), this);
    TopicStore::unsubscribe(m_event, this);
    TopicStore::unsubscribe(m_controlWord, this);
    TopicStore::unsubscribe(m_gameSpecificMessage, this);
    TopicStore::unsubscribe(m_redAlliance, this);
    TopicStore::unsubscribe(m_matchNumber, this);
    TopicStore::unsubscribe(m_matchType, this);
    TopicStore::unsubscribe(m_allianceStation, this);
}

void FMSInfoWidget::setValue(nt::Value &value) {
    qDebug() << "Updatesd :)";
    m_eventString = QString::fromStdString(m_event->GetString("Unknown"));
    m_eventLabel->setText("Event: " + m_eventString);

    m_gsm = QString::fromStdString(m_gameSpecificMessage->GetString("Unknown"));
    m_gsmLabel->setText("Game Specific Message:\n" + m_gsm);

    int station = m_allianceStation->GetInteger(1);
    if (m_redAlliance->GetBoolean(false)) {
        station += 3;
    }

    m_station = (AllianceStation) station;
    m_stationLabel->setText("Station: " + StationNames.value(m_station));

    m_number = m_matchNumber->GetInteger(0);
    m_type = (MatchType) m_matchNumber->GetInteger(0);

    m_matchLabel->setText("Match: " +
                          MatchTypeNames.value(m_type) +
                          " Match " +
                          QString::number(m_number));

    m_word = (ControlWord) m_controlWord->GetInteger(0);

    QString state = "Robot State: ";

    if (m_word | ControlWord::Auto) {
        state += "Autonomous";
    }
    else if (m_word | ControlWord::Test) {
        state += "Testing";
    } else if (m_word | ControlWord::EStop) {
        state += "E-Stopped";
    } else {
        state += "Teleop";
    }

    if (m_word | ControlWord::Enabled) {
        state += " Enabled";
    } else {
        state += " Disabled";
    }

    m_controlLabel->setText(state);

    if (m_word | ControlWord::FMSAttached) {
        m_fmsLabel->setText("FMS Attached");
        m_fmsIconLabel->setPixmap(QIcon(":/check.svg").pixmap(20, 20));
    } else {
        m_fmsLabel->setText("FMS Disconnected");
        m_fmsIconLabel->setPixmap(QIcon(":/xmark.svg").pixmap(20, 20));
    }

    if (m_word | ControlWord::DSAttached) {
        m_fmsLabel->setText("DS Attached");
        m_fmsIconLabel->setPixmap(QIcon(":/check.svg").pixmap(20, 20));
    } else {
        m_fmsLabel->setText("DS Disconnected");
        m_fmsIconLabel->setPixmap(QIcon(":/xmark.svg").pixmap(20, 20));
    }
}

void FMSInfoWidget::forceUpdate() {
    auto placeholder = nt::Value::MakeString("");
    setValue(placeholder);
}
