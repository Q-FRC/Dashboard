#include "widgets/SendableFieldWidget.h"

#include "stores/TopicStore.h"

SendableFieldWidget::~SendableFieldWidget() {
    TopicStore::unsubscribe(m_topic.toStdString(), shared_from_this());
}
