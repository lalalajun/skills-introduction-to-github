#pragma once
#include <vector>
#include <fstream>
#include "computerRoom.h"
#include "identity.h"
#include "globalFile.h"
#include <string>
#include "orderFile.h"

class Student : public Identity {
public:
    //默认构造
    Student();

    //有参构造（学号，姓名，密码）
    Student(int id,string name,string pwd);

    //菜单界面
    void virtual operMenu() override;

    //申请预约
    void applyOrder();

    //查看预约（封装打印机预约记录函数）
    //void showOrder(int& i,OrderFile& of);

    //查看我的预约
    void showMyorder();

    //查看所有预约
    void showAllOrder();

    //取消预约
    void cancelOrder();

    //学生学号
    int m_Id;

    //机房容器
    vector<ComputerRoom>vCom;
};
// Created by 方洋 on 24-9-3.
//

#ifndef STUDENT_H
#define STUDENT_H

#endif //STUDENT_H
