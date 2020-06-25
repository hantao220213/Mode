//
// Created by hantao on 20-5-5.
//

#ifndef XTHREADFTPSERVER_XFTPUSER_H
#define XTHREADFTPSERVER_XFTPUSER_H

#include "XFtpTask.h"

class XFtpUSER: public XFtpTask {
public:
    XFtpUSER();
    ~XFtpUSER();
     virtual void Parse(string cmd,string msg);

};


#endif //XTHREADFTPSERVER_XFTPUSER_H
