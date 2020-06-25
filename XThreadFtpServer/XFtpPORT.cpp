//
// Created by hantao on 20-5-5.
//

#include "ThreadPool/XFtpPORT.h"
#include <iostream>
#include <string>
#include <vector>
using namespace std;

XFtpPORT::XFtpPORT() {

}
XFtpPORT::~XFtpPORT() {

}
void XFtpPORT::Parse(string cmd, string msg) {


    cout <<"XFtpPORT::Parse msg: "<<msg<<endl;
    vector<string>ve;

    if(cmd == "PORT")
    {
        string str="";

        for (int i = 5; i < msg.size(); ++i) {
            if (msg[i] == ','||msg[i] == '\r') {
                ve.push_back(str);
                str="";
                continue;
            }
            str+=msg[i];
        }
        if(ve.size() !=6){
            cout << " recv PORT cmd ERROR"<<endl;
            ResponseMsg("501 Syntax error in parameters or arguments.");
            return;
        }

        ip=ve[0]+"."+ve[1]+"."+ve[2]+"."+ve[3];
        port=atoi(ve[4].c_str())*256+atoi(ve[5].c_str());
        cout<<" ip : "<< ip<<endl;
        cout<<"port: "<<port<<endl;
        msg="200 OK recv port sucess\r\n";
    }
    ResponseMsg(msg);

}