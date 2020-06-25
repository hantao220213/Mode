//
// Created by hantao on 20-5-4.
//

#ifndef XTHREADFTPSERVER_XTASK_H
#define XTHREADFTPSERVER_XTASK_H


class XTask {

public:
    struct  event_base *base=0;
    int socket=0;
    int thread_id=0;
    //	//初始化任务 ，用户列表
    virtual bool Init()=0;
};


#endif //XTHREADFTPSERVER_XTASK_H
