#ifndef TASKMANAGE_H
#define TASKMANAGE_H

#include "MapStructure.h"
#include "routingalgorithm.h"

class TaskManage
{
public:
    TaskManage(uint16_t agvId, const NodeInfo& startNode, const NodeInfo& destNode);

    deque<NodeInfo*> commulatePath() noexcept;

    NodeInfo getDsetNode() noexcept {return m_destNode;}

    uint16_t getAgvId() noexcept {return m_agvId;}

private:
    NodeInfo m_startNode;
    NodeInfo m_destNode;
    uint16_t m_agvId;

    RoutingAlgorithm routeAlgthm;


};

#endif // TASKMANAGE_H
