#ifndef TASKMODULECENTER_H
#define TASKMODULECENTER_H

#include "routingalgorithm.h"
#include <QSettings>
#include "taskmanage.h"
#include "AgvState.h"
#include "agvmodulecenter.h"
#include "chart.h"

class TaskModuleCenter
{
public:
    TaskModuleCenter();
    ~TaskModuleCenter();

    void getTask() noexcept;

    void createTask(Chart *chart) noexcept;

private:

    float getTaskNodeAngle(std::deque<NodeInfo*> taskNodeDeque) noexcept;

    std::map<uint16_t, TaskManage*> m_taskMap;
    std::map<uint16_t, TaskNodeInfo*> m_taskNodeMap;
    NodeInfo m_nodeMap[ROW+1][COLUMN+1];

    std::map<uint16_t, NodeInfo*> m_nodeInfoMap;

    AgvModuleCenter m_agvModuleCenter;

};

#endif // TASKMODULECENTER_H
