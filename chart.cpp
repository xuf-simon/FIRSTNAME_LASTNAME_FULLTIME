#include "chart.h"
#include <QtCharts/QAbstractAxis>
#include <QtCharts/QSplineSeries>
#include <QtCharts/QValueAxis>
#include <QtCore/QRandomGenerator>
#include <QtCore/QDebug>

Chart::Chart(QGraphicsItem *parent, Qt::WindowFlags wFlags):
    QChart(QChart::ChartTypeCartesian, parent, wFlags),
    m_axisX(new QValueAxis()),
    m_axisY(new QValueAxis())
{

    addAxis(m_axisX,Qt::AlignBottom);
    addAxis(m_axisY,Qt::AlignLeft);

    m_axisX->setRange(0, 10);
    m_axisY->setRange(0, 10);
    m_axisX->setTickCount(11);
    m_axisY->setTickCount(11);

}

Chart::~Chart()
{
    delete m_axisX;
    delete m_axisY;

    auto it = m_splineSeriesMap.begin();
    while(it != m_splineSeriesMap.end())
    {
        auto m_lineSeries = it->second;
        delete m_lineSeries;
    }

}

void Chart::init()
{
    setTitle(u8"RoadMap");
    legend()->hide();
    setAnimationOptions(QChart::AllAnimations);
}


void Chart::createAgent(Agent* agent)
{
    QSplineSeries* m_lineSeries = new QSplineSeries(this);
    QPen green(agent->getAgvId() == 1 ? Qt::red : Qt::green);
    green.setWidth(3);
    m_lineSeries->setPen(green);

    addSeries(m_lineSeries);
    m_lineSeries->attachAxis(m_axisX);
    m_lineSeries->attachAxis(m_axisY);

    m_splineSeriesMap[agent->getAgvId()] = m_lineSeries;
}

void Chart::move(uint16_t agvId, float x, float y)
{
    QSplineSeries* m_lineSeries = m_splineSeriesMap[agvId];
    m_lineSeries->append(x, y);
}



