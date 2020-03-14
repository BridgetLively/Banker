#ifndef BANKER_H
#define BANKER_H

#include<stdio.h>
#include<stdbool.h>
#include<stdlib.h>
#include<vector>
using namespace std;

class Banker
{
public:
    Banker();
    int n,m;//进程数、资源数

    vector<vector<int>>max;//各进程所需资源数最大值
    vector<vector<int>>allocation;//系统当前已分配资源数
    vector<int>available;//系统当前可用资源数

    vector<vector<int>>need;//当前各进程所需资源数
    vector<int>work;//进行安全检测时的工作向量，用于显示系统当前可用资源数
    vector<int>securityList;//安全序列
    vector<int>requestList;//进程请求各类资源数

    //备用数组
    vector<vector<int>>allocation1;
    vector<vector<int>>need1;
    vector<int>available1;

    vector<bool>finish;//记录系统能否有足够向量分给进程

    vector<vector<int>> calculateNeed();//计算need数组

    bool compareNW(int i);//用于比较need数组和work数组的大小
    bool compareRN(int i);//用于比较requestList数组和need数组的大小
    bool compareRA();//用于比较requestList数组和available数组的大小

    bool isNewSecurity=true;//第一次安全检测的标志
    void updateWork(int i);//更新work数组
    bool securityTest();//安全性算法

    bool request(int i);//进程请求资源算法

};

#endif // BANKER_H
