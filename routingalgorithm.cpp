#include "routingalgorithm.h"

RoutingAlgorithm::RoutingAlgorithm()
    :m_aStar(new AStar)
{

}

RoutingAlgorithm::~RoutingAlgorithm()
{
    delete m_aStar;
}

/*
 *
 * 初始化节点nodeMap
 *
 */
void RoutingAlgorithm::init(NodeInfo startNode, NodeInfo destNode) noexcept
{
    for(int i = 0; i <= ROW; i++)
    {
        for(int j = 0; j <= COLUMN ; j++)
        {
            nodeMap[i][j] = MapManege::getInstance()->nodeMap[i][j];
            nodeMap[i][j].hvalue = (abs(i-destNode.posX)+abs(j-destNode.posY)) * validLength;
        }

    }

    m_aStar->setNodeMap((NodeInfo*)nodeMap);
}
