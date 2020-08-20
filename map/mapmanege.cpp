#include "mapmanege.h"

MapManege::MapManege()
{
    init();
}

MapManege::~MapManege()
{

}

MapManege* MapManege::getInstance() noexcept
{
    static MapManege instance;

    return &instance;
}


void MapManege::init() noexcept
{
    //’æµ„≥ı ºªØ
    uint32_t nodeId = 0;

    for(int i=0; i <= 10; i++)
    {
        for(int j =0; j <= 10; j++)
        {
            nodeMap[i][j].id = nodeId;
            nodeMap[i][j].posX = i;
            nodeMap[i][j].posY = j;
            nodeMap[i][j].father = nullptr;
            nodeMap[i][j].st = UNSORTED;
            nodeMap[i][j].angle = 0;
            nodeMap[i][j].maxParkingNum = 1;

            m_nodeInfoMap.insert(std::make_pair(nodeId, &nodeMap[i][j]));

            nodeId++;
        }
    }

}

NodeInfo *MapManege::getNodeMap() noexcept
{
   return (NodeInfo*)nodeMap;
}

