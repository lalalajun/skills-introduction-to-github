#include "teacher.h"

//默认构造
Teacher::Teacher() {
}

//有参构造
Teacher::Teacher(int empId, string name, string pwd) {
    //初始化属性
    this->m_empId=empId;
    this->m_Name=name;
    this->m_Pwd=pwd;
}

//查看所有预约
void Teacher::showAllOrder() {
    OrderFile of;
    if(of.m_Size==0) {
        cout<<"无预约记录"<<endl;
        return;
    }

    for(int i=0;i<of.m_Size;i++) {
        cout<<i+1<<". ";
        of.showOrder(i,of);
    }

}

//菜单界面
void Teacher::operMenu() {
    cout<<"欢迎教师："<<this->m_Name<<"登录!"<<endl;
    cout<<"\t\t-------------------------------"<<endl;
    cout<<"\t\t|                             |"<<endl;
    cout<<"\t\t|         1.查看所有预约        |"<<endl;
    cout<<"\t\t|                             |"<<endl;
    cout<<"\t\t|         2.审核预约            |"<<endl;
    cout<<"\t\t|                             |"<<endl;
    cout<<"\t\t|         0.注销登录            |"<<endl;
    cout<<"\t\t|                             |"<<endl;
    cout<<"\t\t-------------------------------"<<endl;
    cout<<"请输入您的选择:"<<endl;
}

//审核预约
void Teacher::validOrder() {
    OrderFile of;
    if(of.m_Size==0) {
        cout<<"无预约记录"<<endl;
        return;
    }

    vector<int>v;
    int index=0;
    cout<<"待审核预约记录如下"<<endl;
    for(int i=0;i<of.m_Size;i++) {
        if(of.m_orderDate[i]["status"]=="1") {
            v.push_back(i);
            cout<<++index<<". ";
            of.showOrder(i,of);
        }
    }

    if(v.size()==0) {
        cout<<"无待审核预约记录"<<endl;
        return;
    }

    cout<<"请输入审核的预约记录，0代表返回"<<endl;
    int select=0;
    int ret=0;
    while (true) {
        cin>>select;
        if(select>=0 && select<=v.size()) {
            if(select==0) {
                break;
            }
            else {
                cout<<"请输入审核结果"<<endl;
                cout<<"1.通过"<<endl;
                cout<<"2.不通过"<<endl;
                cin>>ret;

                if(ret==1) {
                    of.m_orderDate[v[ret-1]]["status"]="2";
                }
                else {
                    of.m_orderDate[v[ret-1]]["status"]="-1";
                }
                of.updatFile();
                cout<<"审核完毕!"<<endl;
                break;;
            }
        }
        else {
            cout<<"输入有误，请重新输入"<<endl;
        }
    }
}




// Created by 方洋 on 24-9-4.
//
