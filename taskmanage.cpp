#include "taskmanage.h"

TaskManage::TaskManage(uint16_t agvId, const NodeInfo& startNode, const NodeInfo& destNode)
    :m_agvId(agvId)
{
	m_startNode = NodeInfo(startNode);
	m_destNode = NodeInfo(destNode);
    //nodeInfoAttrCopy(startNode, m_startNode);
    //odeInfoAttrCopy(destNode, m_destNode);

}

std::list<uint16_t> TaskManage::commulatePath() noexcept
{
    std::list<uint16_t> pathList;

    routeAlgthm.init(m_startNode, m_destNode);
    AStar* star = routeAlgthm.getAstar();

    if(star->findPath(m_startNode,m_destNode))
    {
        pathList = star->getPathList();
    }

    return pathList;
}

void TaskManage::nodeInfoAttrCopy(NodeInfo f_nodeInfo, NodeInfo& b_nodeInfo) noexcept
{

    b_nodeInfo.id = f_nodeInfo.id;
    b_nodeInfo.st = f_nodeInfo.st;
    b_nodeInfo.posX = f_nodeInfo.posX;
    b_nodeInfo.posY = f_nodeInfo.posY;
    b_nodeInfo.angle = f_nodeInfo.angle;

}
