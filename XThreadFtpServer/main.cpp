#include <iostream>
#include <string.h>
#include <string>
#include "include/event2/event.h"
#include "include/event2/http.h"
#include "include/event2/buffer.h"
#include "include/event2/listener.h"
#include <signal.h>

#include "ThreadPool/XThreadPool.h"
#include "ThreadPool/XFtpFactory.h"
#define PORT 8888
using namespace std;

void connlistener_cb(struct evconnlistener *evlisten, evutil_socket_t sock, struct sockaddr *sin, int socklen, void *asgs){

    cout <<" connect listener cb"<<endl;
    XTask *task = XFtpFactory::Get()->CreateTask();
    task->socket=sock;
    XThreadPool::Get()->Dispatich(task);
}


int main() {

    if (signal(SIGPIPE,SIG_IGN)==SIG_ERR)
        return 0;

    //init thread pool
    int threadCount=10;
    XThreadPool::Get()->Init(threadCount);
    //1 初始化线程池
    //XThreadPool *x= new XThreadPool(10);
    //x->Init();

    event_base *base = event_base_new();
    sockaddr_in sin;
    memset(&sin,0,sizeof(sin));
    sin.sin_family=AF_INET;
    sin.sin_port =htons(PORT);
    evconnlistener *ev = evconnlistener_new_bind(base,connlistener_cb,base,LEV_OPT_REUSEABLE|LEV_OPT_CLOSE_ON_FREE,

                                                    6,(sockaddr *)&sin,sizeof(sin));


    if (base)
        event_base_dispatch(base);
    if (ev)
        evconnlistener_free(ev);
    if (base)
        event_base_free(base);
    std::cout << "Hello, World!" << std::endl;
    return 0;
}