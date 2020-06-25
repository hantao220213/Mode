//
// Created by hantao on 20-5-5.
//

#ifndef XTHREADFTPSERVER_XFTPFACTORY_H
#define XTHREADFTPSERVER_XFTPFACTORY_H

#include "XTask.h"

class XFtpFactory {

public:
    static XFtpFactory *Get(){
        static XFtpFactory xFtpFactory;
        return &xFtpFactory;
    }
    XTask *CreateTask();


private:
    XFtpFactory(){};
};


#endif //XTHREADFTPSERVER_XFTPFACTORY_H
