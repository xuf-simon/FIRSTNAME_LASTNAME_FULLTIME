#ifndef AGVMANAGE_H
#define AGVMANAGE_H

#include <QObject>
#include "AgvState.h"
#include <QThread>
#include "mapmanege.h"

class AgvManage
{
public:
    AgvManage(uint16_t agvId, const AgvParameter& paramater);
    ~AgvManage();

    void setTaskInfo(TaskNodeInfo* taskNodeInfo) noexcept;

    void onLine() noexcept;
    void offLine() noexcept;

    void run() noexcept;

    void updateCurrentState() noexcept;

    void setTaskState(bool isChanged) noexcept;

    uint16_t getNextTargetNode() noexcept;

private:
    uint16_t m_agvId;
    float m_startPositionX;
    float m_startPositionY;
    float m_angle;
    AgvParameter m_paramater;
    AgvCurrentState m_agvCurrentState;
    TaskNodeInfo* m_taskNodeInfo;
    uint16_t m_nextTargetCode;

    std::map<uint16_t, NodeInfo*> m_nodeInfoMap;

    bool m_currentTaskChanged;

    bool m_isRunning;
    std::future<void> m_agvRun_futrue;

    std::mutex m_mutexAgvRun;

};

#endif // AGVMANAGE_H
