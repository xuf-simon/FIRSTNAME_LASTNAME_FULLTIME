#ifndef AGVSTATE_H
#define AGVSTATE_H

#include <QObject>

typedef struct
{
    uint16_t agv_Id = 0;
    uint16_t heartBeat = 0;
    uint16_t taskId = 0;
    uint8_t  taskState = 1; // 1 ���� 2 ����
    uint16_t startCodeNum;
    uint16_t currentCodeNum = 0;
    uint16_t targetCodeNum;
    float walkDistance = 0;
    uint8_t  loginState = 0;  //0: δ��¼ 1:�ѵ�¼
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

    uint16_t m_targetNodeNum; // Ŀ��վ���
    float m_x;
    float m_y;
    bool m_isNeedStop; //�Ƿ���ֹͣ��
    float m_agvRunDirection = 0;
    float m_maxSpeed; // ��·���ٶ�
    float m_distance; // ��·�ξ���

    std::list<uint16_t> taskNodeList;
};


#endif // AGVSTATE_H
