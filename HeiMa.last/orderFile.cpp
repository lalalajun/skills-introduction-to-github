#include "orderFile.h"

//构造函数
OrderFile::OrderFile() {
    ifstream ifs;
    ifs.open(ORDER_FILE,ios::in);

    string date;     //日期
    string interval; //时间段
    string stuId;    //学生编号
    string stuName;  //学生姓名
    string roomId;   //机房编号
    string status;   //预约状态

    this->m_Size=0;  //预约记录条数

    while (ifs>>date && ifs>>interval && ifs>>stuId && ifs>>stuName && ifs>>roomId && ifs>>status) {
        string key;
        string value;
        map<string,string>m;

        int pos=date.find(":");
        if (pos!=-1) {
            key=date.substr(0,pos);
            value=date.substr(pos+1,date.size()-pos-1);
            m.insert(make_pair(key,value));
        }

        pos=interval.find(":");
        if (pos!=1) {
            key=interval.substr(0,pos);
            value=interval.substr(pos+1,interval.size()-pos-1);
            m.insert(make_pair(key,value));
        }

        pos=stuId.find(":");
        if (pos!=-1) {
            key=stuId.substr(0,pos);
            value=stuId.substr(pos+1,stuId.size()-pos-1);
            m.insert(make_pair(key,value));
        }

        pos=stuName.find(":");
        if (pos!=-1) {
            key=stuName.substr(0,pos);
            value=stuName.substr(pos+1,stuName.size()-pos-1);
            m.insert(make_pair(key,value));
        }

        pos=roomId.find(":");
        if (pos!=-1) {
            key=roomId.substr(0,pos);
            value=roomId.substr(pos+1,roomId.size()-pos-1);
            m.insert(make_pair(key,value));
        }

        pos=status.find(":");
        if (pos!=-1) {
            key=status.substr(0,pos);
            value=status.substr(pos+1,status.size()-pos-1);
            m.insert(make_pair(key,value));
        }

        this->m_orderDate.insert(make_pair(this->m_Size,m));
        this->m_Size++;
    }
    ifs.close();
}

//更新预约记录
void OrderFile::updatFile() {
    if(this->m_Size==0) {
        return;
    }

    ofstream ofs(ORDER_FILE,ios::trunc);
    for(int i=0;i<this->m_Size;i++) {
        ofs<<"date:"<<this->m_orderDate[i]["date"]<<" "
           <<"interval:"<<this->m_orderDate[i]["interval"]<<" "
           <<"stuId:"<<this->m_orderDate[i]["stuId"]<<" "
           <<"stuName:"<<this->m_orderDate[i]["stuName"]<<" "
           <<"roomId:"<<this->m_orderDate[i]["roomId"]<<" "
           <<"status:"<<this->m_orderDate[i]["status"]<<endl;
    }
    ofs.close();
}

//查看预约
void OrderFile::showOrder(int &i, OrderFile &of) {
    cout<<"预约日期：周"<<of.m_orderDate[i]["date"];
    cout<<"\t\t预约时段："<<(of.m_orderDate[i]["interval"] == "1" ? "上午" : "下午");
    cout<<"\t预约机房："<<of.m_orderDate[i]["roomId"];
    string status="\t预约状态：";
    if(of.m_orderDate[i]["status"]=="1") {
        status+="审核中";
    }
    else if(of.m_orderDate[i]["status"]=="2") {
        status+="预约成功";
    }
    else if(of.m_orderDate[i]["status"]=="-1") {
        status+="审核未通过，预约失败";
    }
    else if(of.m_orderDate[i]["status"]=="0") {
        status+="预约已取消";
    }
    cout<<status<<endl;
}

// Created by 方洋 on 24-9-14.
//
