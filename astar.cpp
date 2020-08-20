#include "astar.h"
#include <iostream>
#include <QDebug>

AStar::AStar()
{

}

//将起点加入openTable，设置优先级最高
void AStar::setStartNode(const NodeInfo& startNode) noexcept
{
    nodeMap[startNode.posX][startNode.posY].st = OPEN;
    nodeMap[startNode.posX][startNode.posY].gvalue = 0;
    m_startNode = NodeInfo(startNode);

    openTable.push_back(&nodeMap[startNode.posX][startNode.posY]);
}

bool AStar::isExsit(NodeInfo *node) noexcept
{
    deque<NodeInfo*>::iterator it;
    for(it = closeTable.begin(); it < closeTable.end(); it++)
    {
        if((*it)->id == node->id)
        {
            return true;
        }
    }

    return false;
}

/*
 *
 * 遍历节点n(row,col)所有的邻近节点
 * 如果邻近节点m在closeTable中, 则跳过，选取下一个邻近节点
 * validLength 为固定代价 10
 *
 * 分别从节点n的上下左右进行查找邻接节点m
 *
 */

void AStar::openNeighbor(int row,int col) noexcept
{
    //将节点n(row,col) 从openTable中删除，并加入closeTable中
    deque<NodeInfo*>::iterator it;
    for(it = openTable.begin(); it < openTable.end(); it++)
    {
        if((*it)->id == (nodeMap[row][col].id))
        {
            nodeMap[row][col].st = CLOSED;
            openTable.erase(it);
            closeTable.push_back(&nodeMap[row][col]);
            break;
        }
    }

    //上
    if(row-1 >= 0)
    {
        if(nodeMap[row-1][col].st == OPEN)//检查该节点是否有更优的G值

        {
            if(nodeMap[row-1][col].gvalue>nodeMap[row][col].gvalue+ validLength)
            {
                nodeMap[row-1][col].gvalue = nodeMap[row][col].gvalue+ validLength;
                nodeMap[row-1][col].father = &nodeMap[row][col];
            }
        }
        else if(nodeMap[row-1][col].st == UNSORTED) //将节点m加入openTable中
        {
            nodeMap[row-1][col].st = OPEN;
            nodeMap[row-1][col].father = &nodeMap[row][col]; //设置节点n为父节点
            nodeMap[row-1][col].gvalue = validLength + nodeMap[row][col].gvalue;
            openTable.push_back(&nodeMap[row-1][col]);
        }
    }
    //右
    if(col+1 <= COLUMN)
    {
        if(nodeMap[row][col+1].st == OPEN)
        {
            if(nodeMap[row][col+1].gvalue>nodeMap[row][col].gvalue + validLength)
            {
                nodeMap[row][col+1].gvalue = nodeMap[row][col].gvalue + validLength;
                nodeMap[row][col+1].father = &nodeMap[row][col];
            }
        }
        else if(nodeMap[row][col+1].st == UNSORTED)
        {
            nodeMap[row][col+1].st = OPEN;
            nodeMap[row][col+1].father = &nodeMap[row][col];
            nodeMap[row][col+1].gvalue = validLength +nodeMap[row][col].gvalue;
            openTable.push_back(&nodeMap[row][col+1]); //将节点m加入openTable中
        }
    }
    //下
    if(row+1 <= ROW)
    {
        if(nodeMap[row+1][col].st == OPEN)
        {
            if(nodeMap[row+1][col].gvalue > nodeMap[row][col].gvalue + validLength)
            {
                nodeMap[row+1][col].gvalue = nodeMap[row][col].gvalue + validLength;
                nodeMap[row+1][col].father = &nodeMap[row][col];
            }
        }
        else if(nodeMap[row+1][col].st == UNSORTED)
        {
            nodeMap[row+1][col].st = OPEN;
            nodeMap[row+1][col].father = &nodeMap[row][col];
            nodeMap[row+1][col].gvalue = validLength + nodeMap[row][col].gvalue;
            openTable.push_back(&nodeMap[row+1][col]); //将节点m加入openTable中
        }
    }
    //左
    if(col-1 >= 0)
    {
        if(nodeMap[row][col-1].st == OPEN)
        {
            if(nodeMap[row][col-1].gvalue>nodeMap[row][col].gvalue + validLength)
            {
                nodeMap[row][col-1].gvalue = nodeMap[row][col].gvalue + validLength;
                nodeMap[row][col-1].father = &nodeMap[row][col];
            }
        }
        else if(nodeMap[row][col-1].st == UNSORTED)
        {
            nodeMap[row][col-1].st = OPEN;
            nodeMap[row][col-1].father = &nodeMap[row][col];
            nodeMap[row][col-1].gvalue = validLength + nodeMap[row][col].gvalue;
            openTable.push_back(&nodeMap[row][col-1]); //将节点m加入openTable中
        }
    }

}


bool AStar::findPath(const NodeInfo& source, const NodeInfo& dest) noexcept
{
    int minDistence;
    int pos;
    int rowNum,colNum;
    deque<NodeInfo*>::iterator i;


    //初始化openTable和closeTable
    openTable.clear();
    closeTable.clear();

    setStartNode(source);
    m_endNode = NodeInfo(dest);

    while(openTable.size()>0)
    {
        //遍历“开启列表”并寻找最下F值的节点

        minDistence = numeric_limits<int> ::max();
        for(i=openTable.begin(); i<openTable.end(); i++)
        {
            if((((NodeInfo*)*i)->gvalue + ((NodeInfo*)*i)->hvalue)<minDistence)
            {
                minDistence = ((NodeInfo*)*i)->gvalue + ((NodeInfo*)*i)->hvalue;
                rowNum = ((NodeInfo*)*i)->posX;
                colNum = ((NodeInfo*)*i)->posY;
            }
        }

        if(rowNum==dest.posX && colNum==dest.posY)//达到目标节点
        {
            openNeighbor(rowNum,colNum);
            return true;
        }
        else
        {
            openNeighbor(rowNum,colNum);
        }
    }
    return false;
}

void AStar::printPath()
{
    deque<NodeInfo*> dq;
    NodeInfo* p = &nodeMap[m_endNode.posX][m_endNode.posY];
    while(!(p->posX==m_startNode.posX && p->posY==m_startNode.posY))
    {
        dq.push_back(p);
        p=p->father;
    }
    dq.push_back(p);
    for(int i=dq.size()-1; i>=0; i--)
    {
        cout<<"("<<dq[i]->posX<<","<<dq[i]->posY<<")"<<endl;
    }
}

std::list<uint16_t> AStar::getPathList() noexcept
{
    std::list<uint16_t> pathList;

    deque<NodeInfo*> dq;
    NodeInfo* p = &nodeMap[m_endNode.posX][m_endNode.posY];
    while(!(p->posX==m_startNode.posX && p->posY==m_startNode.posY))
    {
        dq.push_back(p);
        p=p->father;
    }
    dq.push_back(p);

    for(int i=dq.size()-1; i>=0; i--)
    {
        qDebug() << "("<<dq[i]->posX<<","<<dq[i]->posY<<")";
        pathList.push_back(dq[i]->id);
    }

    return pathList;
}

void AStar::setNodeMap(NodeInfo* nodeMaps) noexcept
{

    for (int i = 0; i <= ROW; i++)
    {
        for(int j = 0; j <= COLUMN; j++)
        {
            nodeMap[i][j] = *(nodeMaps+i*(COLUMN+1)+j);
        }
    }
}


