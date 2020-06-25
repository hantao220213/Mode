//
// Created by hantao on 20-5-5.
//

#include "ThreadPool/XFtpList.h"
#include <string>
#include <iostream>
using namespace std;
XFtpList::XFtpList() {

}
XFtpList::~XFtpList() {

}

void XFtpList::Parse(string cmd, string msg) {

    cout<<"XFtpList::Parse cmd["<<cmd<<"] "<<msg<<endl;
    if(cmd == "PWD")
    {
        //257 "/" is current directory.
        msg = "257 \"";
        msg += resFtpTask->curDir;
        msg += "\" is current dir.\r\n";
        ResponseMsg(msg);
    }
    else if(cmd == "LIST"){

        msg="drwx------. 59 hantao hantao 4096 5月   4 23:18 hantao\r\n";
        ConnectPORT();
        ResponseMsg("150 Here comes the directory listing.\r\n");


    }
    else if(cmd == "CWD"){

    }
}

void XFtpList::Write(struct bufferevent *bev) {

    Send("226 Transfer complete\r\n");
    Close();
}
void XFtpList::Event(struct bufferevent *bev, short what) {
    if (what & (BEV_EVENT_ERROR|BEV_EVENT_EOF|BEV_EVENT_TIMEOUT)){
        cout <<" BEV_EVENT_ERROR|BEV_EVENT_EOF|BEV_EVENT_TIMEOUT : "<<what<<endl;
        bufferevent_free(bev);
        this->resbev=0; // fang zhi er ci shi fang
    } else if(what &BEV_EVENT_CONNECTED){
        cout<<" XFtpList::Event connect sucess"<<endl;
    }
}



