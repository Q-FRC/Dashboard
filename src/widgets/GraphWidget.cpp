#include "widgets/GraphWidget.h"
#include "stores/TopicStore.h"

GraphWidget::GraphWidget(const QString &topic, const QString &title)
    : BaseWidget(WidgetTypes::Graph, title, topic) {
    m_timer = new QTimer(this);
    m_chart = new QChartView(this);

    connect(m_timer, &QTimer::timeout, this, &GraphWidget::updateGraph);

    m_xAxis = new QValueAxis(this);
    m_xAxis->setTitleText("Time");

    m_yAxis = new QValueAxis(this);
    m_yAxis->setTitleText("Value");

    m_chart->chart()->addAxis(m_xAxis, Qt::AlignBottom);
    m_chart->chart()->addAxis(m_yAxis, Qt::AlignLeft);

    setMaxTimeScale(30.);
    setUpdateFrequency(1.0);

    setMaxYValue(10.0);
    setMinYValue(-10.0);

    m_elapsed.start();

    m_layout->addWidget(m_chart, 1, 0, 3, 1);
}

QList<Globals::Topic> GraphWidget::topics() {
    return m_topics;
}

void GraphWidget::setTopics(QList<Globals::Topic> topics) {
    for (const Globals::Topic & topic : m_topics) {

        if (!topics.contains(topic)) {
            TopicStore::unsubscribe(topic.name.toStdString(), this);
            m_entryMap.remove(topic);

            QLineSeries *series = m_seriesMap.take(topic);
            m_chart->chart()->removeSeries(series);
            delete series;
        }
    }

    for (const Globals::Topic &topic : topics) {
        if (!m_topics.contains(topic)) {
            nt::NetworkTableEntry *entry = TopicStore::subscribeWriteOnly(topic.name.toStdString(), this);

            m_entryMap.insert(topic, entry);

            QLineSeries *series = new QLineSeries;
            series->setName(topic.name);
            series->append(m_elapsed.elapsed() / 1000., TopicStore::getDoubleFromEntry(entry));
            m_chart->chart()->addSeries(series);
            series->attachAxis(m_xAxis);
            series->attachAxis(m_yAxis);

            m_seriesMap.insert(topic, series);
        }
    }

    m_topics = topics;
}


double GraphWidget::maxTimeScale() {
    return m_maxTimeScale;
}

void GraphWidget::setMaxTimeScale(double maxTimeScale) {
    m_maxTimeScale = maxTimeScale;
}

double GraphWidget::updateFrequency() {
    return m_updateFrequency;
}

void GraphWidget::setUpdateFrequency(double frequency) {
    m_updateFrequency = frequency;

    m_timer->stop();
    m_timer->start(frequency * 1000.);
}


double GraphWidget::maxYValue() {
    return m_maxYValue;
}

void GraphWidget::setMaxYValue(double max) {
    m_maxYValue = max;
    m_yAxis->setMax(max);
}

double GraphWidget::minYValue() {
    return m_minYValue;
}

void GraphWidget::setMinYValue(double min) {
    m_minYValue = min;
    m_yAxis->setMin(min);
}


void GraphWidget::updateGraph() {
    double elapsedTime = m_elapsed.elapsed() / 1000.;

    double lowerBound = elapsedTime - m_maxTimeScale;
    if (lowerBound < 0) lowerBound = 0;

    m_xAxis->setRange(lowerBound, elapsedTime);

    for (const Globals::Topic &topic : m_topics) {
        nt::NetworkTableEntry *entry = m_entryMap.value(topic);
        QLineSeries *series = m_seriesMap.value(topic);

        double value = TopicStore::getDoubleFromEntry(entry);

        series->append(elapsedTime, value);
    }
}

void GraphWidget::setValue(const nt::Value &value) {}
