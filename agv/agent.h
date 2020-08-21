#ifndef AGENT_H
#define AGENT_H

#include <deque>
#include "MapStructure.h"

class Agent
{
public:
    Agent(uint16_t agvId);

    uint16_t getAgvId() noexcept {return m_agvId;}

    void setPathSeriesDq(std::deque<NodeInfo*> pathSeriesDq) noexcept;

    std::deque<NodeInfo*> getPathSeriesDq() noexcept {return m_pathSeriesDq;}

private:

    uint16_t m_agvId;

    std::deque<NodeInfo*> m_pathSeriesDq;

};

#endif // AGENT_H
