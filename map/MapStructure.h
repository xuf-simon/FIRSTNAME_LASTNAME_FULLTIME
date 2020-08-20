#ifndef MAPSTRUCTURE_H
#define MAPSTRUCTURE_H

#include <string>
#include <list>
#include <map>
#include <QString>
#include <QRect>

const int ROW = 10;
const int COLUMN = 10;
const int validLength = 10;

enum STATUS
{
    OPEN,
    CLOSED,
    UNSORTED
};

struct NodeInfo
{
public:
    NodeInfo(){}

    NodeInfo(const NodeInfo& nodeInfo)
    {
        id = nodeInfo.id;
        posX = nodeInfo.posX;
		posY = nodeInfo.posY;
        father = nodeInfo.father;
        angle = nodeInfo.angle;
        maxParkingNum = nodeInfo.maxParkingNum;
        gvalue = nodeInfo.gvalue;
        hvalue = nodeInfo.hvalue;
        fvalue = nodeInfo.fvalue;
        st = nodeInfo.st;
    }
    uint32_t id;
    int posX;
    int posY;
    NodeInfo* father;
    uint16_t angle;
    uint16_t maxParkingNum;
    int gvalue;
    int hvalue;
    int fvalue;
    STATUS st;

};


struct LineInfo
{
    uint16_t id;
    NodeInfo* startPos;
    NodeInfo* endPos;
    int orient;
    uint16_t radius;
    uint16_t startAngle;
    uint16_t endAngle;
    uint16_t length;
};

struct AreaInfo
{
    uint16_t areaId;
    QRect areaRect;
    std::list<uint16_t> nodeList;
};





#endif // MAPSTRUCTURE_H
