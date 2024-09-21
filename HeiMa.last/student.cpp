#include "student.h"

//默认构造
Student::Student() {

}


//有参构造（学号，姓名，密码）
Student::Student(int id,string name,string pwd) {
    //初始化属性；
    this->m_Id=id;
    this->m_Name=name;
    this->m_Pwd=pwd;

    //初始化机房信息
    ifstream ifs;
    ifs.open(COMPUTER_FILE,ios::in);
    if(!ifs.is_open()) {
        cout<<"机房文件打开失败，未同步机房信息"<<endl;
        return;
    }

    ComputerRoom cm;
    while (ifs>>cm.m_ComId && ifs>>cm.m_MaxNum) {
        this->vCom.push_back(cm);
    }
    ifs.close();
}

//菜单界面
void Student::operMenu() {
    cout<<"欢迎学生代表："<<this->m_Name<<"登录!"<<endl;
    cout<<"\t\t-------------------------------"<<endl;
    cout<<"\t\t|                             |"<<endl;
    cout<<"\t\t|         1.申请预约            |"<<endl;
    cout<<"\t\t|                             |"<<endl;
    cout<<"\t\t|         2.查看我的预约        |"<<endl;
    cout<<"\t\t|                             |"<<endl;
    cout<<"\t\t|         3.查看所有预约        |"<<endl;
    cout<<"\t\t|                             |"<<endl;
    cout<<"\t\t|         4.取消预约            |"<<endl;
    cout<<"\t\t|                             |"<<endl;
    cout<<"\t\t|         0.注销登录            |"<<endl;
    cout<<"\t\t|                             |"<<endl;
    cout<<"\t\t-------------------------------"<<endl;
    cout<<"请输入您的选择:"<<endl;
}


//申请预约
void Student::applyOrder() {
    cout<<"机房开放时间为周一至周五！"<<endl;
    cout<<"请输入申请预约时间:"<<endl;
    cout<<"1.周一"<<endl;
    cout<<"2.周二"<<endl;
    cout<<"3.周三"<<endl;
    cout<<"4.周四"<<endl;
    cout<<"5.周五"<<endl;

    int date;//预约时间
    int interval;//预约时间断
    int room;//预约机房

    while (true) {
        cin>>date;
        if(date<=5 && date>=1) {
            break;;
        }
        else
            cout<<"输入有误，请重新输入"<<endl;
    }

    cout<<"请输入申请预约时间段："<<endl;
    cout<<"1.上午"<<endl;
    cout<<"2.下午"<<endl;
    while (true) {
        cin>>interval;
        if(2>=interval && interval>=1) {
            break;
        }
        else
            cout<<"输入有误，请重新输入"<<endl;
    }

    cout<<"请输入想预约的机房"<<endl;
    for(int i=0;i<this->vCom.size();i++) {
        cout<<this->vCom[i].m_ComId<<"号机房容量: "<<this->vCom[i].m_MaxNum<<endl;
    }

    while (true) {
        cin>>room;
        if(room>=1 && 3>=room) {
            break;
        }
        else
            cout<<"输入有误，请重新输入"<<endl;
    }

    cout<<"预约成功，审核中！"<<endl;

    ofstream ofs(ORDER_FILE,ios::app);
    ofs<<"date:"<<date<<" ";
    ofs<<"interval:"<<interval<<" ";
    ofs<<"stuId:"<<this->m_Id<<" ";
    ofs<<"stuName:"<<this->m_Name<<" ";
    ofs<<"roomId:"<<room<<" ";
    ofs<<"status:"<<1<<endl;//预约状态

    ofs.close();
}

//查看预约
// void Student::showOrder(int& i,OrderFile& of) {
//     cout<<"预约日期：周"<<of.m_orderDate[i]["date"];
//     cout<<"\t\t预约时段："<<(of.m_orderDate[i]["interval"] == "1" ? "上午" : "下午");
//     cout<<"\t预约机房："<<of.m_orderDate[i]["roomId"];
//     string status="\t预约状态：";
//     if(of.m_orderDate[i]["status"]=="1") {
//         status+="审核中";
//     }
//     else if(of.m_orderDate[i]["status"]=="2") {
//         status+="预约成功";
//     }
//     else if(of.m_orderDate[i]["status"]=="-1") {
//         status+="审核未通过，预约失败";
//     }
//     else if(of.m_orderDate[i]["status"]=="0") {
//         status+="预约已取消";
//     }
//     cout<<status<<endl;
// }


//查看我的预约
void Student::showMyorder() {
    OrderFile of;
    int index=1;

    if(of.m_Size==0) {
        cout<<"无预约记录"<<endl;
        return;
    }

    for(int i=0;i<of.m_Size;i++) {
        if(atoi(of.m_orderDate[i]["stuId"].c_str())==this->m_Id) {
            cout<<index++<<". ";
            of.showOrder(i,of);
        }
    }
    if(index==1) {
        cout<<"无您的预约记录"<<endl;
    }
}

//查看所有预约
void Student::showAllOrder() {
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

//取消预约
void Student::cancelOrder() {
    OrderFile of;
    if(of.m_Size==0) {
        cout<<"无预约记录"<<endl;
        return;
    }

    cout<<"您审核中或预约成功的记录可取消，请输入取消的预约记录"<<endl;

    vector<int>v;
    int index=1;
    for(int i=0;i<of.m_Size;i++) {
        if(this->m_Id==atoi(of.m_orderDate[i]["stuId"].c_str())) {
            if(of.m_orderDate[i]["status"]=="1" || of.m_orderDate[i]["status"]=="2") {
                v.push_back(i);
                cout<<index++<<". ";
                of.showOrder(i,of);
            }
        }
    }

    if(v.size()==0) {
        cout<<"无可取消的预约记录"<<endl;
        return;
    }

    cout<<"请输入取消的预约记录,0代表返回"<<endl;
    int select=0;
    while (true) {
        cin>>select;
        if(select>=0 && select<=v.size() ) {
            if(select==0) {
                break;
            }
            else {
                of.m_orderDate[v[select-1]]["status"]="0";
                of.updatFile();
                cout<<"已取消预约记录"<<endl;
                break;
            }
        }
        else {
            cout<<"输入有误，请重新输入"<<endl;
        }
    }
}
// Created by 方洋 on 24-9-3.
//
