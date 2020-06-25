//
// Created by hantao on 20-5-4.
//

#include "ThreadPool/XFtpServercCMD.h"
#include <iostream>
#include "ThreadPool/XTask.h"
#include "include/event2/bufferevent.h"
#include "include/event2/event.h"
#include <string.h>
using namespace std;


XFtpServercCMD::XFtpServercCMD() {

}
XFtpServercCMD::~XFtpServercCMD() {

    Close();
    for (auto ptr=del_calls.begin();ptr!=del_calls.end();ptr++ ) {
        ptr->first->Close();
        delete ptr->first;

    }

}
void XFtpServercCMD::Read(struct bufferevent *bev) {
    cout <<"read>>>>>>>>>>>>>>>>>>>>:";
    char buf[1024]={0};

    for (;;) {
        int len = bufferevent_read(bev,buf,sizeof(buf)-1);
        if(len <= 0)
            break;
        buf[len]=0;
        cout<<buf<<flush;
        //parse cmd
        string cmdtype ="";
        for (int i = 0; i <len ; ++i) {
            if (buf[i]==' '||buf[i] == '\r')
                break;
            cmdtype+=buf[i];
        }
        cout<<"cmdtype: ["<<cmdtype<<"]"<<endl;
        if (calls.find(cmdtype)!= calls.end()){
            XFtpTask *ftpTask =calls[cmdtype];
            //ftpTask->resbev=bev; //response bev
            ftpTask->resFtpTask=this; //response msg
            ftpTask->ip=ip;
            ftpTask->port=port;
            ftpTask->base=base;

            ftpTask->Parse(cmdtype,buf);
        }
        else
        {
            string tmp="200 OK 404 not found\r\n";
            bufferevent_write(bev,tmp.c_str(),tmp.size());
        }


    }


    //分发日任务

}
void XFtpServercCMD::Write(struct bufferevent *bev) {
    string str = "write_event msg";
    //bufferevent_write(bev,str.c_str(),str.size());
    //bufferevent_free(bev);
    //delete this;
}

void XFtpServercCMD::Event(struct bufferevent *bev, short what) {
    if (what & (BEV_EVENT_ERROR|BEV_EVENT_EOF|BEV_EVENT_TIMEOUT)){
        cout <<" BEV_EVENT_ERROR|BEV_EVENT_EOF|BEV_EVENT_TIMEOUT : "<<what<<endl;
        //bufferevent_free(bev);
        delete this;
    }
}

void XFtpServercCMD::CmdRegister(string cmd, XFtpTask *call) {
    if(!call){
        cout<<" Register call is null" <<endl;
        return;
    }
    if (cmd.empty()){
        cout<<" Register cmd is null" <<endl;
        return;
    }
    //bu fu gai
    if(calls.find(cmd)!=calls.end())
    {
        cout<<" cmd:"<<cmd<<"] is already"<<endl;
        return;
    }
    calls[cmd]=call;
    del_calls[call]=0;

}

bool XFtpServercCMD::Init() {
    cout<<" XFtpServercCMD "<<endl;

    bufferevent *bev = bufferevent_socket_new(base,socket,BEV_OPT_CLOSE_ON_FREE);
    if(!base)
    {
        //bufferevent_free(bev); xi gou hanshu Close()
        delete this;
        return false;
    }
    this->resbev=bev;
    this->SetCallback(bev);
    //timeout
    timeval rtime={30,0};
    timeval wtime={0,0};
    bufferevent_set_timeouts(bev,&rtime,&wtime);

    string msg = "220 WelCome to libevent My ftp server\r\n";
    bufferevent_write(bev,msg.c_str(),msg.size());
}
