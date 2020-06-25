//
// Created by hantao on 20-5-5.
//

#include "ThreadPool/XFtpRETR.h"
#include <iostream>
#include <string>
using namespace std;
XFtpRETR::XFtpRETR() {

}
XFtpRETR::~XFtpRETR() {

}

void XFtpRETR::Parse(string cmd, string msg) {
    if(cmd == "RETR"){

        Send("150 OK\r\n");

        //文件名
        int pos = msg.rfind(" ") + 1;
        string filename = msg.substr(pos, msg.size() - pos - 2);
        string path = resFtpTask->rootDir;
        path += resFtpTask->curDir;
        path += filename;
        fp = fopen(path.c_str(), "rb");
        if (fp)
        {
            //连接数据通道
            ConnectPORT();

            //发送开始下载文件的指令
            ResponseMsg("150 File OK\r\n");

            //触发写入事件
            bufferevent_trigger(resbev, EV_WRITE, 0);
        }
        else
        {
            ResponseMsg("450 file open failed!\r\n");
        }

    }
}
void XFtpRETR::Write(struct bufferevent *bev) {
    if (!fp)
        return;
    int len = fread(buf,1,sizeof(buf)-1,fp);
    if (len <= 0){
        Close();
        return;
    }
    Send(buf,len);

}
void XFtpRETR::Event(struct bufferevent *bev, short what) {
    if (what & (BEV_EVENT_ERROR|BEV_EVENT_EOF|BEV_EVENT_TIMEOUT)){
        cout <<" BEV_EVENT_ERROR|BEV_EVENT_EOF|BEV_EVENT_TIMEOUT : "<<what<<endl;
        bufferevent_free(bev);
        this->resbev=0; // fang zhi er ci shi fang
    } else if(what &BEV_EVENT_CONNECTED){
        cout<<" XFtpList::Event connect sucess"<<endl;
    }
}