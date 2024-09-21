#pragma once
#include <iostream>
#include "computerRoom.h"
#include "student.h"
#include "teacher.h"
using namespace std;
#include "identity.h"
#include <fstream>
#include <vector>
#include <algorithm>

class Manager : public Identity {
public:

    //默认构造
    Manager();

    //有参构造（管理员姓名，密码）
    Manager(string name,string pwd);

    //菜单界面
    void operMenu() override;

    //添加账号
    void addPerson();

    //查看账号
    void showPerson();

    //查看机房信息
    void showComputer();

    //清空预约记录
    void cleanFile();

    //查重函数
    bool checkRepeat(int id,int type);

    //初始化容器
    void initVector();

    //学生容器
    vector<Student>vStu;

    //老师容器
    vector<Teacher>vTea;

    //机房容器
    vector<ComputerRoom>vCom;
};
// Created by 方洋 on 24-9-4.
//

#ifndef MANAGER_H
#define MANAGER_H

#endif //MANAGER_H
