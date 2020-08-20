#ifndef AGVSTATE_H
#define AGVSTATE_H

#include <QObject>

typedef struct
{
    uint16_t agv_Id = 0;
    uint16_t heartBeat = 0;
    uint16_t taskId = 0;
    uint8_t  taskState = 1; // 1 空闲 2 工作
    uint16_t startCodeNum;
    uint16_t currentCodeNum = 0;
    uint16_t targetCodeNum;
    float walkDistance = 0;
    uint8_t  loginState = 0;  //0: 未登录 1:已登录
    uint16_t nextTargetCodeNum;
    float angle = 0;
    float posX = 0;
    float posY = 0;
    float speed;
    bool isOnline;
}AgvCurrentState;

struct AgvParameter
{
    uint16_t type;
    float radius;
    float maxSpeed;
    float acceleration;
    float deceleration;
    uint16_t loginCodeNum;
    float loginPosX;
    float loginPosY;
    float loginAngle;
    const static uint TimeStep = 100;
};

struct TaskNodeInfo
{
public:
    TaskNodeInfo() {}

    TaskNodeInfo(const TaskNodeInfo& taskNodeInfo)
    {
        m_targetNodeNum = taskNodeInfo.m_targetNodeNum;
        m_x = taskNodeInfo.m_x;
        m_y = taskNodeInfo.m_y;
        m_isNeedStop = taskNodeInfo.m_isNeedStop;
        m_agvRunDirection = taskNodeInfo.m_agvRunDirection;
        m_maxSpeed = taskNodeInfo.m_maxSpeed;
        m_distance = taskNodeInfo.m_distance;
        taskNodeList = taskNodeInfo.taskNodeList;
    }

    uint16_t m_targetNodeNum; // 目标站点号
    float m_x;
    float m_y;
    bool m_isNeedStop; //是否是停止点
    float m_agvRunDirection = 0;
    float m_maxSpeed; // 该路段速度
    float m_distance; // 该路段距离

    std::list<uint16_t> taskNodeList;
};


#endif // AGVSTATE_H
