#include "agvmodulecenter.h"

AgvModuleCenter::AgvModuleCenter()
{
    MapManege* m_mapManage = MapManege::getInstance();

    for(int i = 0; i <= ROW; i++)
    {
        for(int j = 0; j <= COLUMN ; j++)
        {
            m_nodeMap[i][j] = m_mapManage->nodeMap[i][j];
        }
    }

    initConf();
}

AgvModuleCenter::~AgvModuleCenter()
{

    stopAllAgv();

}

void AgvModuleCenter::initConf() noexcept
{
    QSettings conf("../config/AGVSetting.ini", QSettings::IniFormat);

    for(auto key : conf.childGroups())
    {
        initAgvParameter();

        uint16_t agvId = conf.value(QString("%1/id").arg(key)).toUInt();
        if (m_AgvMap[agvId])
        {
            continue;
        }

        m_agvParameter.loginPosX = conf.value(QString("%1/startPositionX").arg(key)).toFloat();
        m_agvParameter.loginPosY = conf.value(QString("%1/startPositionY").arg(key)).toFloat();
        m_agvParameter.loginAngle = conf.value(QString("%1/startAngle").arg(key)).toFloat();

        uint16_t loginx = static_cast<uint16_t>(m_agvParameter.loginPosX);
        uint16_t loginy = static_cast<uint16_t>(m_agvParameter.loginPosY);

        m_agvParameter.loginCodeNum = m_nodeMap[loginx][loginy].id;

        AgvManage* agv = new AgvManage(agvId, m_agvParameter);

        m_AgvMap[agvId] = agv;

        std::thread th(&AgvModuleCenter::createAgv, this, agvId);
        th.detach();
    }
}

void AgvModuleCenter::initAgvParameter() noexcept
{
    //AGV默认参数
    m_agvParameter.type = 0; //激光
    m_agvParameter.radius = 0.45;
    m_agvParameter.maxSpeed = 1;
    m_agvParameter.loginPosX = 0;
    m_agvParameter.loginPosY = 0;
    m_agvParameter.loginAngle = 0;
    m_agvParameter.acceleration = 0.2;
    m_agvParameter.deceleration = 0.2;
    m_agvParameter.loginCodeNum = 0;
}

void AgvModuleCenter::createAgv(uint16_t agvId) noexcept
{
    std::unique_lock<std::mutex> locker_login(m_mutexAgvLogin);
    m_AgvMap[agvId]->onLine();
}

void AgvModuleCenter::stopAllAgv()
{
    auto agv_it = m_AgvMap.begin();
    while (agv_it != m_AgvMap.end())
    {
        AgvManage* agv = agv_it->second;
        delete agv;
        agv = nullptr;

        agv_it++;
    }
}

