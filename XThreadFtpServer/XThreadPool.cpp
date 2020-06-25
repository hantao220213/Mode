//
// Created by hantao on 20-5-4.
//


#include "ThreadPool/XThreadPool.h"
#include "ThreadPool/XThread.h"
#include <thread>
#include <iostream>
#include <chrono>
using namespace std;

void XThreadPool::Dispatich(XTask *task) {
    if (!task)
        return;
    int tid = (lasrThread+1)%threadCount;
    lasrThread=tid;
    XThread *xThread = threads[tid];
    //添加任务
    xThread->AddTask(task);
    //激活县城
    xThread->Active();


}
void XThreadPool::Init(int threadCount) {
    this->threadCount=threadCount;
    this->lasrThread=-1;

    for (int i = 0; i <threadCount ; ++i) {
        XThread *xThread = new  XThread();
        xThread->id=i+1;
        xThread->Start();
        threads.emplace_back(xThread);
        std::cout <<" create thread"<<std::endl;
        this_thread::sleep_for(chrono::milliseconds(10));
    }
}

