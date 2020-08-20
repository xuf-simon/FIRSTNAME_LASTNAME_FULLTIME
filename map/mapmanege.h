#ifndef MAPMANEGE_H
#define MAPMANEGE_H

#include <vector>
#include "MapStructure.h"
#include <QString>


class MapManege
{

public:
    MapManege();
    ~MapManege();

    static MapManege* getInstance() noexcept;

    void init() noexcept;

    NodeInfo* getNodeMap() noexcept;

    std::map<uint16_t, NodeInfo*> getNodeInfoMap() noexcept {return m_nodeInfoMap;}

    NodeInfo nodeMap[ROW+1][COLUMN+1];

private:

    std::map<uint16_t, NodeInfo*> m_nodeInfoMap;


};

#endif // MAPMANEGE_H
