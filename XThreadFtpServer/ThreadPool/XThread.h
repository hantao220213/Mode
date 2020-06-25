//
// Created by hantao on 20-5-4.
//

#ifndef XTHREADFTPSERVER_XTHREAD_H
#define XTHREADFTPSERVER_XTHREAD_H
#include "../include/event2/util.h"
#include "../include/event2/event.h"
#include <sys/types.h>
#include <sys/socket.h>
#include <list>
#include <mutex>
#include "XTask.h"
class XTask;

class XThread {
public:
    XThread();
    ~XThread();

    void Start();
    void Main();
    bool Setup();
    void Notify(evutil_socket_t fds, short witch);
    void AddTask(XTask *task);//添加任务
    void Active();// 激活线程
    int id=0;
private:
    int notify_send_fd=0;
    struct event_base *base=0;

    ////任务列表
    std::list<XTask*>tasks;
    std::mutex task_mtx;

};


#endif //XTHREADFTPSERVER_XTHREAD_H
