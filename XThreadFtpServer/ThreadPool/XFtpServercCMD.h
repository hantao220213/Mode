//
// Created by hantao on 20-5-4.
//

#ifndef XTHREADFTPSERVER_XFTPSERVERCCMD_H
#define XTHREADFTPSERVER_XFTPSERVERCCMD_H

#include "XFtpTask.h"
#include <unordered_map>
#include <map>
#include <string>
using namespace std;
class XFtpServercCMD:public XFtpTask {

public:
    XFtpServercCMD();
    ~XFtpServercCMD();
    virtual bool Init();


    virtual void Read(struct bufferevent *bev);
    virtual void Write(struct bufferevent *bev);
    virtual void Event(struct bufferevent *bev, short what);

    //注册命令对象，主线陈调用，县城安全
    void CmdRegister(string cmd,XFtpTask *call);

private:
    std::map<string,XFtpTask*>calls;
    std::map<XFtpTask *,int >del_calls;


};


#endif //XTHREADFTPSERVER_XFTPSERVERCCMD_H
