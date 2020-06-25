//
// Created by hantao on 20-5-5.
//

#ifndef XTHREADFTPSERVER_XFTPRETR_H
#define XTHREADFTPSERVER_XFTPRETR_H

#include "XFtpTask.h"

class XFtpRETR: public XFtpTask{
public:
    XFtpRETR();
    ~XFtpRETR();
    virtual void Parse(string cmd,string msg);
    virtual void Write(struct bufferevent *bev);
    virtual void Event(struct bufferevent *bev, short what);

private:
    char  buf[1024]={0};

};


#endif //XTHREADFTPSERVER_XFTPRETR_H
