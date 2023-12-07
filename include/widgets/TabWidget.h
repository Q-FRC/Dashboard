#pragma once

#include <QGridLayout>
#include <QWidget>
#include <QPoint>

class TabWidget : public QWidget
{
    Q_OBJECT
private:
    QGridLayout *m_layout;
    
    QPoint m_maxSize;
    QPoint m_selectedIndex;

    bool m_hasSelection = false;

    void updateSpacers();
public:
    TabWidget(const QPoint &maxSize);
    virtual ~TabWidget();

    QGridLayout *layout();

    QPoint maxSize();
    void setMaxSize(const QPoint &maxSize);

    QPoint selectedIndex();
    void setSelectedIndex(const QPoint &selectedIndex);

    bool hasSelection();
    void setHasSelection(const bool &hasSelection);

    void paintEvent(QPaintEvent *event) override;
};
