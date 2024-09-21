#pragma once
#include <iostream>
using namespace std;

class Identity {
public:

    virtual void operMenu()=0;//各个身份的菜单基类

    string m_Name;//用户名
    string m_Pwd;//密码
};
// Created by 方洋 on 24-9-3.
//

#ifndef IDENTITY_H
#define IDENTITY_H

#endif //IDENTITY_H
