//
// Created by hantao on 20-5-5.
//

#include "ThreadPool/XFtpUSER.h"
#include <string>
#include <iostream>
using namespace std;
XFtpUSER::XFtpUSER() {

}
XFtpUSER::~XFtpUSER() {

}

void XFtpUSER::Parse(string cmd, string msg) {
    cout<<"XFtpUSER::Parse cmd["<<cmd<<"] "<<msg<<endl;
    ResponseMsg("200 OK\r\n");
}
