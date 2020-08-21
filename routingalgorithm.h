#ifndef ROUTINGALGORITHM_H
#define ROUTINGALGORITHM_H

#include "astar.h"
#include "mapmanege.h"

typedef NodeInfo (*R)[COLUMN];

class RoutingAlgorithm
{
public:
    RoutingAlgorithm();
    ~RoutingAlgorithm();

    void init(NodeInfo startNode, NodeInfo destNode) noexcept;

    AStar* getAstar() {return m_aStar;}

private:
    NodeInfo nodeMap[ROW+1][COLUMN+1];

    AStar* m_aStar;

};

#endif // ROUTINGALGORITHM_H
