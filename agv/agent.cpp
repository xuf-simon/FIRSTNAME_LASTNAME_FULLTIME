#include "agent.h"
#include <QtCharts/QSplineSeries>

Agent::Agent(uint16_t agvId)
    :m_agvId(agvId)
{

}


void Agent::setPathSeriesDq(std::deque<NodeInfo *> pathSeriesDq) noexcept
{
    m_pathSeriesDq = pathSeriesDq;
}
