//
// Created by hantao on 20-5-5.
//

#ifndef XTHREADFTPSERVER_XFTPTASK_H
#define XTHREADFTPSERVER_XFTPTASK_H
#include "../include/event2/bufferevent.h"
#include "../include/event2/event.h"
#include "XTask.h"
#include <string>
using namespace std;
class XFtpTask: public XTask {
public:
    //XFtpTask();
   // ~XFtpTask();
    virtual void Read(struct bufferevent *bev){}
    virtual void Write(struct bufferevent *bev){}
    virtual void Event(struct bufferevent *bev, short what){}

    void SetCallback(struct bufferevent *bev);

    virtual void Parse(string cmd,string msg){};
    virtual bool Init(){ return true;};


    void ResponseMsg(string msg);

    string curDir ="/";
    string rootDir=".";
    XFtpTask *resFtpTask=0;

    string ip="";
    short port=0;
    void ConnectPORT();
    void  Send(string msg);
    void Send(const char *data, int datasize);
    void Close();
protected:
     static void Read_cb(struct bufferevent *bev, void *ctx);
     static void Write_cb(struct bufferevent *bev, void *ctx);
     static void Event_cb(struct bufferevent *bev,short what, void *ctx);

     struct bufferevent *resbev=0; //response bev
     FILE *fp =0;


};


#endif //XTHREADFTPSERVER_XFTPTASK_H
