
#ifndef CHART_H
#define CHART_H

#include <QtCharts/QChart>
#include <QtCore/QTimer>
#include <deque>
#include "MapStructure.h"
#include "agent.h"

QT_CHARTS_BEGIN_NAMESPACE
class QSplineSeries;
class QValueAxis;
QT_CHARTS_END_NAMESPACE

QT_CHARTS_USE_NAMESPACE

//![1]
class Chart: public QChart
{
    Q_OBJECT
public:
    Chart(QGraphicsItem *parent = 0, Qt::WindowFlags wFlags = 0);
    virtual ~Chart();

    void init();

    void createAgent(Agent* agent);

    void move(uint16_t agvId, float x, float y);

private:

    QStringList m_titles;
    QValueAxis *m_axisX;
    QValueAxis *m_axisY;

    std::deque<NodeInfo*> dq;
    std::map<uint16_t, QSplineSeries*> m_splineSeriesMap;

};
//![1]

#endif /* CHART_H */
