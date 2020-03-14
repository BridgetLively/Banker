#include "banker.h"
#include <iostream>
using namespace std;
Banker::Banker()
{

}

//安全性算法
bool Banker::securityTest()
{
    bool security=true;//系统安全标志

    if(isNewSecurity)//进程第一次运行安全性算法
    {
        //为work和finish数组申请空间并赋值
        for(int i=0;i<m;i++)
        {
            work.push_back(available[i]);
        }
        for(int i=0;i<n;i++)
        {
            finish.push_back(false);
        }
        isNewSecurity=false;
    }else
    {
        //直接更改work和finish的值
        for(int i=0;i<m;i++)
        {
            work[i]=available[i];
        }
        for(int i=0;i<n;i++)
        {
            finish[i]=false;
        }
    }
    securityList.clear();//清空原有的安全序列

    for(int i=0;i<n;i++)//循环n次，以确保每个进程都能被正确判断
    {
        for(int j=0;j<n;j++)//从0到n判断进程是否满足以下条件
        {
            if((finish[j]==false)&&(compareNW(j)==true))//系统有资源分配给进程且进程所需资源数小于当前可用资源数
            {
                updateWork(j);
                finish[j]=true;
                securityList.push_back((int)j);
                break;
            }
        }
    }

    //判断系统是否处于安全状态，若不安全则设值security为false
    for(int i=0;i<n;i++)
    {
        if(finish[i]!=true)
        {
            security=false;
            break;
        }
    }
    return security;
}

//进程请求资源算法
bool Banker::request(int i)
{

    bool success=true;//请求资源成功标志

    //清空备用数组
    available1.clear();
    allocation1.clear();
    need1.clear();

    //备用数组，用于分配失败时的资源恢复
    for(int j=0;j<n;j++)
    {
        vector<int>tmp;
        vector<int>tmp1;
        for(int k=0;k<m;k++)
        {
            tmp.push_back(allocation[j][k]);
            tmp1.push_back(need[j][k]);
        }
        allocation1.push_back(tmp);
        need1.push_back(tmp1);
    }
    for(int k=0;k<m;k++)
    {
        available1.push_back(available[k]);
    }

    if(compareRN(i))
    {
        if(compareRA())
        {
            //模拟分配资源
            for(int p=0;p<n;p++)
            {
                available[p]=available[p]-requestList[p];
                allocation[i][p]=allocation[i][p]+requestList[p];
                need[i][p]=need[i][p]-requestList[p];
            }
        }
        else//请求资源大于系统可供资源
        {
            success=false;
        }
    }
    else//错误请求信息
    {
        success=false;
    }

    //假定分配资源后进行安全性检测
    if(success)
    {
        success=securityTest();
    }

    //检测出分配后系统处于不安全状态则撤销分配
    if(!success)
    {
        for(int j=0;j<n;j++)
        {
            for(int k=0;k<m;k++)
            {
                allocation[j][k]=allocation1[j][k];
                need[j][k]=need1[j][k];
                available[k]=available1[k];
            }
        }
    }
    return success;
}

//计算need数组
vector<vector<int>> Banker::calculateNeed()
{
    need.clear();
    for(int i=0;i<n;i++)
    {
        vector<int>tmp;
        for(int j=0;j<m;j++)
        {
            int num=max[i][j]-allocation[i][j];
            if(num>=0)
                tmp.push_back(num);
            else
                tmp.push_back(0);
        }
        need.push_back(tmp);
    }
    return need;
}

/*
 * compareNW: 进程i的need数组和work数组的大小，若need中所有元素对应小于work中元素，则返回true
 * i:进程编号
 */
bool Banker::compareNW(int i)
{
    bool isSmall=true;//小于标志

    for(int j=0;j<m;j++)
    {
        if(need[i][j]>work[j])
        {
            isSmall=false;
            break;
        }
    }
    return isSmall;
}

/*
 * compareRN: 进程i的requestList数组和need数组的大小，若requestList中所有元素对应小于need中元素，则返回true
 * i:进程编号
 */
bool Banker::compareRN(int i)
{
    bool isSmall=true;
    for(int j=0;j<m;j++)
    {
        if(requestList[j]>need[i][j])
        {
            isSmall=false;
            break;
        }
    }
    return isSmall;
}

/*
 * compareRA: 进程i的requestList数组和available数组的大小，若requestList中所有元素对应小于available中元素，则返回true
 */
bool Banker::compareRA()
{
    bool isSmall=true;
    for(int j=0;j<m;j++)
    {
        if(requestList[j]>available[j])
        {
            isSmall=false;
            break;
        }
    }
    return isSmall;
}

/*
 * updateWork: 更新工作向量work
 * i:进程编号
 */
void Banker::updateWork(int i)
{
    for(int j=0;j<m;j++)
    {
        work[j]=work[j]+allocation[i][j];
    }
}
