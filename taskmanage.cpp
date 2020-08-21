#include "taskmanage.h"

TaskManage::TaskManage(uint16_t agvId, const NodeInfo& startNode, const NodeInfo& destNode)
    :m_agvId(agvId)
{
	m_startNode = NodeInfo(startNode);
	m_destNode = NodeInfo(destNode);

}

deque<NodeInfo*> TaskManage::commulatePath() noexcept
{
    deque<NodeInfo*> pathDeque;

    routeAlgthm.init(m_startNode, m_destNode);
    AStar* star = routeAlgthm.getAstar();

    if(star->findPath(m_startNode,m_destNode))
    {
        pathDeque = star->getPathDeque();
    }

    return pathDeque;
}
