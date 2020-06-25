//
// Created by hantao on 20-5-4.
//

#include "ThreadPool/XThread.h"
#include <thread>
#include <iostream>
#include <unistd.h>

using namespace std;
using namespace this_thread;

static void Notify_cb(evutil_socket_t fd, short witch, void *args)
{
    XThread *xThread = (XThread*)args;
    xThread->Notify(fd,witch);
}
void XThread::Notify(evutil_socket_t fds, short witch) {
    char buf[2]={0};
    int len = read(fds,buf,1);
    if(len <=0 )
        return;
    cout << id << " thread " << buf << endl;

    XTask *task = NULL;
    task_mtx.lock();
    cout << id << " tasks " << tasks.size() << endl;

    if (tasks.empty())
    {
        task_mtx.unlock();
        return;
    }

    task= tasks.front();
    tasks.pop_front();
    task_mtx.unlock();
    task->Init();

}

void XThread::AddTask(XTask *task) {

    if(tasks.size() > 1024)
        return;

    task->base=this->base; //chuan di base
    task_mtx.lock();
    tasks.push_back(task);
    task_mtx.unlock();
}
// 激活线程
void XThread::Active() {
    int ret = write(this->notify_send_fd,"c",1);
    if(ret <=0)
    {
        cout<<" Active thread failed"<<endl;
        return;
    }

}
XThread::XThread() {

}
XThread::~XThread() {

}

void XThread::Start() {
    Setup();
    thread th(&XThread::Main,this);
    th.detach();
}
void XThread::Main() {

    cout<<"ID: "<<id<<" get_id: "<<get_id()<<endl;
    event_base_dispatch(base);
    if (base)
        event_base_free(base);
}

bool XThread::Setup() {

    int fds[2]; //fds[0]---read fds[1]---write
    if (pipe(fds)){
        cout<< " pipe error"<<endl;
        return false;
    }

    //read bind  event and save
    notify_send_fd=fds[1];
    //create libevent shang xia wen (no lock)
    event_config *eventConfig = event_config_new();
    event_config_set_flag(eventConfig,EVENT_BASE_FLAG_NOLOCK);
    this->base=event_base_new_with_config(eventConfig);
    event_config_free(eventConfig);
    if(!base)
    {
        cout<< " create event_config base failed"<<endl;
        return false;
    }

    //添加管监听事件，用于激活线程
    event *ev = event_new(base,fds[0],EV_READ|EV_PERSIST,Notify_cb,this);
    event_add(ev,0);

}