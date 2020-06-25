//
// Created by hantao on 20-5-5.
//

#include "ThreadPool/XFtpTask.h"
#include <string.h>
/*
XFtpTask::XFtpTask() {

}
XFtpTask::~XFtpTask() {

}
 */

void XFtpTask::ResponseMsg(string msg) {
    if (!(resFtpTask) || !(resFtpTask->resbev))
        return;
    bufferevent_write(resFtpTask->resbev,msg.c_str(),msg.size());
}


void XFtpTask::SetCallback(struct bufferevent *bev) {
    bufferevent_setcb(bev,Read_cb,Write_cb,Event_cb,this);
    bufferevent_enable(bev,EV_READ|EV_WRITE);

}

void XFtpTask::Read_cb(struct bufferevent *bev, void *ctx) {
    XFtpTask *ftpTask = (XFtpTask*)ctx;
    ftpTask->Read(bev);

}

void XFtpTask::Write_cb(struct bufferevent *bev, void *ctx) {
    XFtpTask *ftpTask = (XFtpTask*)ctx;
    ftpTask->Write(bev);

}
void XFtpTask::Event_cb(struct bufferevent *bev, short what, void *ctx) {
    XFtpTask *ftpTask = (XFtpTask*)ctx;
    ftpTask->Event(bev,what);
}

void XFtpTask::ConnectPORT() {
    if (!base || !ip.empty()||!resFtpTask)
        return;
    resbev = bufferevent_socket_new(base,-1,BEV_OPT_CLOSE_ON_FREE);
    sockaddr_in sin;
    memset(&sin,0,sizeof(sin));

    sin.sin_family=AF_INET;
    sin.sin_port=htons(port);
    evutil_inet_pton(AF_INET,ip.c_str(),&sin.sin_addr.s_addr);
    SetCallback(resbev);
    timeval rtm={0,0};
    timeval wtm={10,0};
    bufferevent_set_timeouts(resbev,&rtm,&wtm);

    bufferevent_socket_connect(resbev,(sockaddr*)&sin,sizeof(sin));


}

void XFtpTask::Send(string msg) {
    Send(msg.c_str(),msg.size()); // Send(const char *data, int datasize)
}
void XFtpTask::Send(const char *data, int datasize) {
    if(!resbev)
        return;
    bufferevent_write(resbev,data,datasize);
}
void XFtpTask::Close() {
    if(resbev)
    {
        bufferevent_free(resbev);
        this->resbev=0;
    }
    if (fp)
    {
        fclose(fp);
        fp=0;
    }
}