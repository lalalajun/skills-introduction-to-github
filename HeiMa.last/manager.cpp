#include "manager.h"

#include "globalFile.h"

//默认构造
Manager::Manager() {

}

//有参构造
Manager::Manager(string name, string pwd) {
    this->m_Name=name;
    this->m_Pwd=pwd;

    //初始化容器
    this->initVector();

    //初始化机房信息
    ifstream ifs;
    ifs.open(COMPUTER_FILE,ios::in);
    if(!ifs.is_open()) {
        cout<<"机房信息打开失败，请检查机房信息"<<endl;
        return;
    }

    ComputerRoom cr;
    while (ifs>>cr.m_ComId && ifs>>cr.m_MaxNum) {
        this->vCom.push_back(cr);
    }

    ifs.close();
}

//菜单界面
void Manager::operMenu() {
    cout<<"欢迎管理员："<<this->m_Name<<"登录!"<<endl;
    cout<<"\t\t-------------------------------"<<endl;
    cout<<"\t\t|                             |"<<endl;
    cout<<"\t\t|         1.添加账号            |"<<endl;
    cout<<"\t\t|                             |"<<endl;
    cout<<"\t\t|         2.查看账号            |"<<endl;
    cout<<"\t\t|                             |"<<endl;
    cout<<"\t\t|         3.查看机房            |"<<endl;
    cout<<"\t\t|                             |"<<endl;
    cout<<"\t\t|         4.清空预约            |"<<endl;
    cout<<"\t\t|                             |"<<endl;
    cout<<"\t\t|         0.注销登录            |"<<endl;
    cout<<"\t\t|                             |"<<endl;
    cout<<"\t\t-------------------------------"<<endl;
    cout<<"请输入您的选择:"<<endl;
}

//添加账号
void Manager::addPerson() {
    cout<<"请输入添加账号类型"<<endl;
    cout<<"1.添加学生"<<endl;
    cout<<"2.添加老师"<<endl;

    string fileName;
    string tip;
    string errorTip;
    ofstream ofs;

    int select;
    cin>>select;

    if(select==1) {
        fileName=STUDENT_FILE;
        tip="请输入学号";
        errorTip="学号重复，请重新输入";
    }
    else {
        fileName=TEACHER_FILE;
        tip="请输入教师编号";
        errorTip="教师编号重复，请重新输入";
    }

    ofs.open(fileName,ios::out | ios::app);

    int id;
    string name;
    string pwd;

    cout<<tip<<endl;
    while (true) {
        cin>>id;

        bool ret=checkRepeat(id,select);
        if(ret) {
            cout<<errorTip<<endl;
        }
        else {
            break;
        }
    }

    cout<<"请输入姓名"<<endl;
    cin>>name;
    cout<<"请输入密码"<<endl;
    cin>>pwd;

    ofs<<id<<" "<<name<<" "<<pwd<<endl;
    cout<<"添加成功"<<endl;

    ofs.close();

    //初始化容器
    this->initVector();
}

//查看账号
void printStudent(Student &s) {
    cout<<"学号： "<<s.m_Id<<"\t姓名： "<<s.m_Name<<"\t密码： "<<s.m_Pwd<<endl;
}

void printTeacher(Teacher &t) {
    cout<<"教师编号： "<<t.m_empId<<"\t姓名： "<<t.m_Name<<"\t密码： "<<t.m_Pwd<<endl;
}

void Manager::showPerson() {
    cout<<"请选择查看内容"<<endl;
    cout<<"1.查看所有学生"<<endl;
    cout<<"2.查看所有教师"<<endl;

    int select=0;
    cin>>select;

    while(true) {
        if(select==1) {
            cout<<"所有学生信息如下："<<endl;
            for_each(vStu.begin(),vStu.end(),printStudent);
            break;
        }
        else if(select==2) {
            cout<<"所有教师信息如下"<<endl;
            for_each(vTea.begin(),vTea.end(),printTeacher);
            break;
        }
        else {
            cout<<"输入有误，请重新输入"<<endl;
            cin>>select;
        }
    }
}

//查看机房信息
void Manager::showComputer() {
    cout<<"机房信息如下:"<<endl;
    for(vector<ComputerRoom>::iterator it=vCom.begin();it!=vCom.end();it++) {
        cout<<"机房编号： "<<it->m_ComId<<"\t机房最大容量: "<<it->m_MaxNum<<endl;
    }
}

//清空预约记录
void Manager::cleanFile() {
    ofstream ofs;
    ofs.open(ORDER_FILE,ios::trunc);

    cout<<"清空成功!"<<endl;
}

//初始化容器
void Manager::initVector() {
    vStu.clear();
    vTea.clear();

    ifstream ifs;
    //读取学生文件信息
    ifs.open(STUDENT_FILE,ios::in);
    if(!ifs.is_open()) {
        cout<<"文件读取失败"<<endl;
        return;
    }

    Student s;
    while(ifs>>s.m_Id && ifs>>s.m_Name && ifs>>s.m_Pwd) {
        vStu.push_back(s);
    }
    ifs.close();

    //读取老师文件信息
    ifs.open(TEACHER_FILE,ios::in);
    if(!ifs.is_open()) {
        cout<<"文件读取失败"<<endl;
        return;
    }

    Teacher t;
    while(ifs>>t.m_empId && ifs>>t.m_Name && ifs>>t.m_Pwd) {
            vTea.push_back(t);
    }
    ifs.close();
}

//检查是否重复
bool Manager::checkRepeat(int id,int type) {
    if(type==1) {
        for(vector<Student>::iterator it=vStu.begin();it!=vStu.end();it++) {
            if(id==it->m_Id) {
                return true;
            }
        }
    }
    else{
        for(vector<Teacher>::iterator it=vTea.begin();it!=vTea.end();it++) {
            if(id==it->m_empId) {
                return true;
            }
        }
    }
    return false;
}


// Created by 方洋 on 24-9-4.
//
