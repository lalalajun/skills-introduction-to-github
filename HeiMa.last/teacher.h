//
#pragma once
#include <iostream>
using namespace std;
#include "identity.h"
#include "orderFile.h"

class Teacher : public Identity{
public:

    //默认构造
    Teacher();

    //有参构造(教师编号，姓名，密码)
    Teacher(int empId,string name,string pwd);

    //菜单界面
    virtual void operMenu() override;

    //查看所有预约
    void showAllOrder();

    //审核预约
    void validOrder();

    int m_empId;//教师编号
};
//

#ifndef TEACHER_H
#define TEACHER_H

#endif //TEACHER_H
