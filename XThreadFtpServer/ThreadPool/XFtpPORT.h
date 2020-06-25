//
// Created by hantao on 20-5-5.
//

#ifndef XTHREADFTPSERVER_XFTPPORT_H
#define XTHREADFTPSERVER_XFTPPORT_H

#include "XFtpTask.h"

class XFtpPORT :public XFtpTask{

public:
    XFtpPORT();
    ~XFtpPORT();
    virtual void Parse(string cmd,string msg);

};


#endif //XTHREADFTPSERVER_XFTPPORT_H
