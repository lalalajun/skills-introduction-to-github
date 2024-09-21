#include <iostream>
#include "manager.h"
#include "student.h"
#include "teacher.h"
using namespace std;
#include "identity.h"
#include "globalFile.h"
#include <fstream>
#include <string>

//管理员菜单
void managerMenu(Identity* &manager) {
    while(true) {
        //管理员基类菜单
        manager->operMenu();

        Manager* man=(Manager*)manager;

        int select=0;
        cin>>select;

        switch (select) {
            case 1:
                cout<<"添加账号"<<endl;
                man->addPerson();
            break;
            case 2:
                cout<<"查看账号"<<endl;
                man->showPerson();
            break;
            case 3:
                cout<<"查看机房"<<endl;
                man->showComputer();
            break;
            case 4:
                cout<<"清空预约"<<endl;
                man->cleanFile();
            break;
            case 0:
                cout<<"注销登陆"<<endl;
                delete man;
                cout<<"注销成功"<<endl;
            return;
            break;
            default:
                cout<<"输入有误，请重新输入"<<endl;
            break;
        }
    }
}

//学生菜单
void studentMenu(Identity* &student) {
    while (true) {
        //学生菜单
        student->operMenu();

        Student* stu=(Student*)student;

        int select=0;
        cin>>select;

        switch (select) {
            case 1:
                cout<<"申请预约"<<endl;
                stu->applyOrder();
            break;
            case 2:
                cout<<"查看自身预约"<<endl;
                stu->showMyorder();
            break;
            case 3:
                cout<<"查看所有预约"<<endl;
                stu->showAllOrder();
            break;
            case 4:
                cout<<"取消预约"<<endl;
                stu->cancelOrder();
            break;
            case 0:
                cout<<"注销登陆"<<endl;
                delete stu;
                cout<<"注销成功"<<endl;
                return;
            default:
                cout<<"输入有误，请重新输入"<<endl;
            break;
        }
    }
}

//教师菜单
void teacherMenu(Identity* &teacher) {
    while (true) {
        //教师菜单
        teacher->operMenu();

        Teacher* tea=(Teacher*)teacher;

        int select=0;
        cin>>select;

        switch (select) {
            case 1:
                cout<<"查看所有预约"<<endl;
                tea->showAllOrder();
            break;;
            case 2:
                cout<<"审核预约"<<endl;
                tea->validOrder();
            break;
            case 0:
                cout<<"注销登陆"<<endl;
                delete tea;
                cout<<"注销成功"<<endl;
                return;
            break;
            default:
                cout<<"输入有误，请重新输入"<<endl;
            break;
        }
    }
}

//登陆功能
void loginIn(string fileName,int type) {

    Identity* person=NULL;

    ifstream ifs;
    ifs.open(fileName,ios::in);

    if(!ifs.is_open()) {
        cout<<"文件不存在"<<endl;
        ifs.close();
        return;
    }

    int id=0;
    string name;
    string pwd;

    if(type==1) {
        cout<<"请输入你的学号"<<endl;
        cin>>id;
    }
    else if(type==2) {
        cout<<"请输入你的教职工号"<<endl;
        cin>>id;
    }

    cout<<"请输入姓名"<<endl;
    cin>>name;

    cout<<"请输入密码"<<endl;
    cin>>pwd;

    int fId;
    string fName;
    string fPwd;
    if(type==1) {
        //学生登陆
        while(ifs>>fId && ifs>>fName && ifs>>fPwd) {
            if(id==fId && name==fName && pwd==fPwd) {
                cout<<"学生验证登陆成功！"<<endl;

                person=new Student(id,name,pwd);
                studentMenu(person);

                return;
            }
        }
    }
    else if(type==2) {
        //教师登陆验证
        while(ifs>>fId && ifs>>fName && ifs>>fPwd) {
            if(id==fId && name==fName && pwd==fPwd) {
                cout<<"教师验证登陆成功！"<<endl;

                person=new Teacher(id,name,pwd);
                teacherMenu(person);

                return;
            }
        }
    }
    else if(type==3) {
        //管理员登陆验证
        while(ifs>>fName && ifs>>fPwd) {
            if(name==fName && pwd==fPwd) {
                cout<<"管理员验证登陆成功！"<<endl;

                person=new Manager(name,pwd);
                managerMenu(person);

                return;
            }
        }
    }

    cout<<"输入有误，验证登陆失败"<<endl;

    return;
}


int main() {
            int select;

            while(true) {

                cout<<"===============欢迎来到黑马机房预约系统================"<<endl;
                cout<<"请输入您的身份:"<<endl;
                cout<<"\t\t-------------------------------"<<endl;
                cout<<"\t\t|                             |"<<endl;
                cout<<"\t\t|         1.学生代表            |"<<endl;
                cout<<"\t\t|                             |"<<endl;
                cout<<"\t\t|         2.老   师            |"<<endl;
                cout<<"\t\t|                             |"<<endl;
                cout<<"\t\t|         3.管 理 员           |"<<endl;
                cout<<"\t\t|                             |"<<endl;
                cout<<"\t\t|         0.退   出            |"<<endl;
                cout<<"\t\t|                             |"<<endl;
                cout<<"\t\t-------------------------------"<<endl;
                cout<<"请输入您的选择:"<<endl;

                cin>>select;

                switch (select) {
                    case 1://学生身份
                        loginIn(STUDENT_FILE,1);
                    break;
                    case 2://老师身份
                        loginIn(TEACHER_FILE,2);
                    break;
                    case 3://管理员身份
                        loginIn(ADMIN_FILE,3);
                    break;
                    case 0://退出系统
                        cout<<"欢迎下一次使用！"<<endl;
                        return 0;
                    break;
                    default:
                        cout<<"输入有误，请重新输入！"<<endl;
                    break;
                }
            }
            return 0;
        }
