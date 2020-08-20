#include "taskmodulecenter.h"
#include <QDebug>

TaskModuleCenter::TaskModuleCenter()
{
    MapManege* m_mapManage = MapManege::getInstance();
    m_nodeInfoMap = m_mapManage->getNodeInfoMap();

    for(int i = 0; i <= ROW; i++)
    {
        for(int j = 0; j <= COLUMN ; j++)
        {
            m_nodeMap[i][j] = m_mapManage->nodeMap[i][j];
        }
    }
}

TaskModuleCenter::~TaskModuleCenter()
{

}

void TaskModuleCenter::getTask() noexcept
{

    uint16_t taskId = 1;

    QSettings conf("../config/TaskSetting.ini", QSettings::IniFormat);
    for(auto key : conf.childGroups())
    {
        if (m_taskMap[taskId])
        {
            continue;
        }

        uint16_t agvId = conf.value(QString("%1/agvId").arg(key)).toUInt();
        float startPosX = conf.value(QString("%1/startPositionX").arg(key)).toFloat();
        float startPosY = conf.value(QString("%1/startPositionY").arg(key)).toFloat();
        float startAngle = conf.value(QString("%1/startAngle").arg(key)).toFloat();

        int startX = static_cast<int>(startPosX);
        int startY = static_cast<int>(startPosY);


        float goalPosX = conf.value(QString("%1/goalPositionX").arg(key)).toFloat();
        float goalPosY = conf.value(QString("%1/goalPositionY").arg(key)).toFloat();
        float goalAngle = conf.value(QString("%1/goalAngle").arg(key)).toFloat();

        int goalX = static_cast<int>(goalPosX);
        int goalY = static_cast<int>(goalPosY);

        NodeInfo startNode;
        startNode.posX = startX;
        startNode.posY = startY;
        startNode.angle = startAngle;

        startNode.id = m_nodeMap[startX][startY].id;

        NodeInfo goalNode;
        goalNode.posX = goalX;
        goalNode.posY = goalY;
        goalNode.angle = goalAngle;

        goalNode.id = m_nodeMap[goalX][goalY].id;

        TaskManage* taskManage = new TaskManage(agvId, startNode, goalNode);
		m_taskMap[taskId] = taskManage;

        taskId++;
    }

}

void TaskModuleCenter::createTask() noexcept
{
    auto task_it = m_taskMap.begin();

    while(task_it != m_taskMap.end())
    {
        auto taskManege = task_it->second;

        auto agvId = taskManege->getAgvId();
        qDebug() << "AGV:" << agvId;

        TaskNodeInfo* taskNodeInfo = new  TaskNodeInfo();
        taskNodeInfo->m_targetNodeNum = taskManege->getDsetNode().id;
        taskNodeInfo->taskNodeList = taskManege->commulatePath();


        std::list<uint16_t> taskNodeList = taskNodeInfo->taskNodeList;
        taskNodeInfo->m_agvRunDirection = getTaskNodeAngle(taskNodeList);

        m_taskNodeMap[task_it->first] = taskNodeInfo;


        auto m_AgvMap = m_agvModuleCenter.getAgvMap();

        AgvManage* agvManege = m_AgvMap[agvId];
        agvManege->setTaskInfo(taskNodeInfo);

        std::thread th(&AgvManage::onLine, agvManege);
        th.detach();

        task_it++;
    }

}

float TaskModuleCenter::getTaskNodeAngle(std::list<uint16_t> taskNodeList) noexcept
{
    float angle = 0;

    auto first_it = taskNodeList.begin();
    uint16_t startId = *first_it;
    first_it++;
    uint16_t secondId = *first_it;

    float startx = m_nodeInfoMap[startId]->posX;
    float starty = m_nodeInfoMap[startId]->posY;

    float secondx = m_nodeInfoMap[secondId]->posX;
    float secondy = m_nodeInfoMap[secondId]->posY;


    if(startx - secondx < 0)
    {
        angle = 0;
    }

    if(starty - secondy < 0)
    {
        angle = 90;
    }

    if(startx - secondx > 0)
    {
        angle = 180;
    }

    if(starty - secondy > 0)
    {
        angle = 360;
    }

    return angle;
}
