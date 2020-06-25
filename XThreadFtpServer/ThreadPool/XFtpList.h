//
// Created by hantao on 20-5-5.
//

#ifndef XTHREADFTPSERVER_XFTPLIST_H
#define XTHREADFTPSERVER_XFTPLIST_H

#include "XFtpTask.h"
class XFtpList : public XFtpTask {

public:
    XFtpList();
    ~XFtpList();
    virtual void Parse(string cmd,string msg);
    virtual void Write(struct bufferevent *bev);
    virtual void Event(struct bufferevent *bev, short what);


};


#endif //XTHREADFTPSERVER_XFTPLIST_H
