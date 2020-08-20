#ifndef ASTAR_H
#define ASTAR_H

#include <deque>
#include "MapStructure.h"
#include <vector>


using namespace std;

class AStar
{
public:
    AStar();

    bool findPath(const NodeInfo& source, const NodeInfo& dest) noexcept;

    void printPath();

    std::list<uint16_t> getPathList() noexcept;

    void setNodeMap(NodeInfo* nodeMaps) noexcept;

    void nodeInfocopy(NodeInfo f_nodeInfo, NodeInfo& b_nodeInfo) noexcept;

private:
    void openNeighbor(int row,int col) noexcept;
     void setStartNode(const NodeInfo& startNode) noexcept;
     bool isExsit(NodeInfo* node) noexcept;

private:
	deque<NodeInfo*> openTable;
    deque<NodeInfo*> closeTable;
    NodeInfo m_startNode;
    NodeInfo m_endNode;

    NodeInfo nodeMap[ROW+1][COLUMN+1];



};

#endif // ASTAR_H
