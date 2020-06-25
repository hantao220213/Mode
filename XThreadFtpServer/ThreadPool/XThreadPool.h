//
// Created by hantao on 20-5-4.
//

#ifndef XTHREADFTPSERVER_XTHREADPOOL_H
#define XTHREADFTPSERVER_XTHREADPOOL_H


#include <vector>
#include "XTask.h"

class XThread;
class XTask;
class XThreadPool {
public:
    //dan jian mo shi
    static XThreadPool *Get(){
        static XThreadPool pool;
        return &pool;
    }

    //init thread pool and start pool
     void Init(int );

    void Dispatich(XTask *task);

private:
    //thread number
    int  threadCount=0;
    int lasrThread=-1; //loop point
    //xian cheng chi xian cheng
    std::vector<XThread*>threads;
    XThreadPool(){};


};


/*
//duo xian cheng chi
class XThread;

class XThreadPool
{
public:


/*
    //单件模式
    static XThreadPool* Get()
    {
        static XThreadPool p;
        return &p;
    }
    */
     /*
    //初始化所有线程并启动线程
     void Init();
     XThreadPool(int n):threadCount(n){};


private:
    //线程数量
    int threadCount = 0;
    //线程池线程
    std::vector<XThread *>threads;


};
*/

#endif //XTHREADFTPSERVER_XTHREADPOOL_H
