#pragma once
#include <iostream>
using namespace std;
#include "globalFile.h"
#include <map>
#include <fstream>
#include <string>

class OrderFile {
public:

    //构造函数
    OrderFile();

    //更新预约记录
    void updatFile();

    //查看预约
    void showOrder(int &i,OrderFile &of);

    //记录预约信息容器，key-----记录预约条数，value-----具体预约记录键值对信息
    map<int,map<string,string>>m_orderDate;

    //预约记录条数
    int m_Size;
};
// Created by 方洋 on 24-9-14.
//

#ifndef ORDERFILE_H
#define ORDERFILE_H

#endif //ORDERFILE_H
