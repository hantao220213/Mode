//
// Created by hantao on 20-5-5.
//

#include "ThreadPool/XFtpFactory.h"
#include "ThreadPool/XFtpServercCMD.h"
#include "ThreadPool/XFtpUSER.h"
#include "ThreadPool/XFtpList.h"
#include "ThreadPool/XFtpPORT.h"
#include "ThreadPool/XFtpRETR.h"
XTask* XFtpFactory::CreateTask() {
    XFtpServercCMD *FtpServercCMD = new XFtpServercCMD();

    //
    FtpServercCMD->CmdRegister("USER",new XFtpUSER());

    //xFtpServercCMD->CmdRegister("list", new XFtpList());
    //xFtpServercCMD->CmdRegister("pwd", new XFtpList());
    XFtpList *FtpList = new XFtpList();
    FtpServercCMD->CmdRegister("PWD",FtpList);
    FtpServercCMD->CmdRegister("LIST",FtpList);
    FtpServercCMD->CmdRegister("CWD",FtpList);

    XFtpPORT *ftpPORT = new XFtpPORT();
    FtpServercCMD->CmdRegister("PORT",ftpPORT);

    XFtpRETR *ftpRETR = new XFtpRETR();
    FtpServercCMD->CmdRegister("RETR",ftpRETR);



    return FtpServercCMD;
}
