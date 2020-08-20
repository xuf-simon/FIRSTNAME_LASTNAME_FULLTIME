#ifndef AGVMODULECENTER_H
#define AGVMODULECENTER_H

#include <QSettings>
#include "agvmanage.h"
#include <QThread>
#include <mutex>

class AgvModuleCenter
{
public:
    AgvModuleCenter();
    ~AgvModuleCenter();

    std::map<uint16_t, AgvManage*> getAgvMap() noexcept {return m_AgvMap;}

private:
    void initConf() noexcept;

    void initAgvParameter() noexcept;

    void createAgv(uint16_t agvId) noexcept;

    void stopAllAgv();

private:
    std::map<uint16_t, AgvManage*> m_AgvMap;
    AgvParameter m_agvParameter;
    NodeInfo m_nodeMap[ROW+1][COLUMN+1];

    std::mutex m_mutexAgvLogin;

};

#endif // AGVMODULECENTER_H
