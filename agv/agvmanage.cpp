#include "agvmanage.h"
#include <QDebug>
#include <thread>

AgvManage::AgvManage(uint16_t agvId, const AgvParameter& paramater)
    :m_agvId(agvId)
    ,m_startPositionX(paramater.loginPosX)
    ,m_startPositionY(paramater.loginPosY)
    ,m_angle(paramater.loginAngle)
    ,m_paramater(paramater)
    ,m_currentTaskChanged(false)
    ,m_isRunning(false)
    ,m_taskNodeInfo(nullptr)
{
    m_agvCurrentState.agv_Id = agvId;
    m_agvCurrentState.isOnline = false;
    m_agvCurrentState.posX = paramater.loginPosX;
    m_agvCurrentState.posY = paramater.loginPosY;
    m_agvCurrentState.angle = paramater.loginAngle;
    m_agvCurrentState.currentCodeNum = paramater.loginCodeNum;


    m_nodeInfoMap = MapManege::getInstance()->getNodeInfoMap();

}

AgvManage::~AgvManage()
{
    m_isRunning = false;
    if (m_agvRun_futrue.valid())
    {
        m_agvRun_futrue.wait();//等待run线程结束
    }

}

void AgvManage::setTaskInfo(TaskNodeInfo* taskNodeInfo) noexcept
{
    m_taskNodeInfo = taskNodeInfo;
}

void AgvManage::onLine() noexcept
{

    //login
    //draw
    m_isRunning = true;
    m_agvRun_futrue = std::async(std::launch::async, &AgvManage::run, this);

}

void AgvManage::offLine() noexcept
{
    m_agvCurrentState.isOnline = false;
}

void AgvManage::run() noexcept
{

    std::unique_lock<std::mutex> locker_login(m_mutexAgvRun);
    m_agvCurrentState.loginState = 1;//登录
    m_agvCurrentState.isOnline = true;

    while (m_isRunning)
    {
        if(m_taskNodeInfo == nullptr)
        {
            QThread::msleep(AgvParameter::TimeStep);
            continue;
        }

        if(m_agvCurrentState.currentCodeNum == m_taskNodeInfo->m_targetNodeNum)
        {
             m_taskNodeInfo->m_isNeedStop = true;
        }
        else
        {

            float diatance = 1;
            m_agvCurrentState.walkDistance = 0;

            m_nextTargetCode = getNextTargetNode();

            while(!m_currentTaskChanged) //如果当前任务没有变化，AGV持续运动
            {
                auto walkDistance = (m_paramater.maxSpeed * AgvParameter::TimeStep / 1000);
                m_agvCurrentState.speed = m_paramater.maxSpeed;

                m_agvCurrentState.walkDistance +=  walkDistance;
                diatance = diatance - walkDistance;

                auto agvRunAngle = int(m_taskNodeInfo->m_agvRunDirection);
                if(agvRunAngle == 0)//targetAngle
                    m_agvCurrentState.posX += walkDistance;
                else if(agvRunAngle == 90)
                    m_agvCurrentState.posY += walkDistance;
                else if(agvRunAngle == 180)
                    m_agvCurrentState.posX -= walkDistance;
                else if(agvRunAngle == 360)
                    m_agvCurrentState.posY -= walkDistance;
                else
                {
                    m_agvCurrentState.posX += walkDistance * cos(3.1415927 * agvRunAngle / 180);
                    m_agvCurrentState.posY += walkDistance * sin(3.1415927 * agvRunAngle / 180);
                }

                qDebug() << "agvId:" << m_agvCurrentState.agv_Id
                    << "pox:" << m_agvCurrentState.posX << "poy:" << m_agvCurrentState.posY
                    << "diatance:" << diatance << "walkDistance:" << walkDistance;

                if(diatance < walkDistance)//判断是否到达节点
                {
                    m_agvCurrentState.currentCodeNum = m_nextTargetCode;//更新站台号
                    m_agvCurrentState.posX = m_nodeInfoMap[m_nextTargetCode]->posX; //消除误差
                    m_agvCurrentState.posY = m_nodeInfoMap[m_nextTargetCode]->posY;

                    if(m_taskNodeInfo->m_isNeedStop)
                    {
                        m_agvCurrentState.speed = 0;
                    }
                    if(m_agvCurrentState.currentCodeNum == m_agvCurrentState.targetCodeNum)
                    {
                        m_agvCurrentState.speed = 0;
                        setTaskState(false);
                    }
                    break;
                }

                QThread::msleep(AgvParameter::TimeStep*10);

            }

        }

    }

}

void AgvManage::setTaskState(bool isChanged) noexcept
{
    m_currentTaskChanged = isChanged;
}

uint16_t AgvManage::getNextTargetNode() noexcept
{
    uint16_t nextNodeNum = m_taskNodeInfo->taskNodeList.front();
    m_taskNodeInfo->taskNodeList.remove(nextNodeNum);

    m_currentTaskChanged = false;

    if (m_nodeInfoMap[m_agvCurrentState.currentCodeNum]->posX - m_nodeInfoMap[nextNodeNum]->posX < 0)
    {
        m_taskNodeInfo->m_agvRunDirection = 0;
    }

    if (m_nodeInfoMap[m_agvCurrentState.currentCodeNum]->posY - m_nodeInfoMap[nextNodeNum]->posY < 0)
    {
        m_taskNodeInfo->m_agvRunDirection = 90;
    }

    if (m_nodeInfoMap[m_agvCurrentState.currentCodeNum]->posX - m_nodeInfoMap[nextNodeNum]->posX > 0)
    {
        m_taskNodeInfo->m_agvRunDirection = 180;
    }

    if (m_nodeInfoMap[m_agvCurrentState.currentCodeNum]->posY - m_nodeInfoMap[nextNodeNum]->posY > 0)
    {
        m_taskNodeInfo->m_agvRunDirection = 360;
    }


    return nextNodeNum;
}
