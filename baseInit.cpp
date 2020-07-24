//
// Created by hjx on 7/23/20.
//

#include "baseInit.h"
#include <QObject>
void CALLBACK DisConnectFunc(LLONG lLoginID,char *pchDVRIP, LONG nDVRPort, LDWORD dwUser){
//    baseInit * pThis = (baseInit *)dwUser;
//    if(NULL == pThis)
//    {
//        return;
//    }
//    //deal
//    QEvent*  eventDisconnect = new QEvent(QEvent::User);
//    QApplication::postEvent((QObject*)pThis, eventDisconnect);
//    return;

    std::cout << "Receive disconnect message, where ip:" << pchDVRIP <<
         " and port:" << nDVRPort << " and login handle:" << lLoginID <<
         std::endl;
    
};

void baseInit::initData(QString Ip) {
    CLIENT_Init(DisConnectFunc,(LDWORD)this);
    m_lLoginHandle = 0;
    QString strIp = Ip;
    QString strUserName = "admit";
    QString strDvrPort = "37777";
    QString strPassword = "37777";

    int error = 0;
    //get number
    bool numok;
    long lPort = strDvrPort.toLong(&numok);
    if(numok) {
        NET_IN_LOGIN_WITH_HIGHLEVEL_SECURITY stInparam;
        memset(&stInparam, 0, sizeof(stInparam));
        stInparam.dwSize = sizeof(stInparam);
        strncpy(stInparam.szIP, (char *) strIp.toUtf8().data(), sizeof(stInparam.szIP) - 1);
        strncpy(stInparam.szPassword, (char *) strPassword.toUtf8().data(), sizeof(stInparam.szPassword) - 1);
        strncpy(stInparam.szUserName, (char *) strUserName.toUtf8().data(), sizeof(stInparam.szUserName) - 1);
        stInparam.nPort = lPort;
        stInparam.emSpecCap = EM_LOGIN_SPEC_CAP_TCP;

        NET_OUT_LOGIN_WITH_HIGHLEVEL_SECURITY stOutparam;
        memset(&stOutparam, 0, sizeof(stOutparam));
        stOutparam.dwSize = sizeof(stOutparam);
        m_lLoginHandle = CLIENT_LoginWithHighLevelSecurity(&stInparam, &stOutparam);

        if (m_lLoginHandle == 0) {

            std::cout << "Login failed " << std::endl;

            if (stOutparam.nError != 255) {
                //QMessageBox::about(this, QObject::tr("Prompt"), QObject::tr("Login failed!"));
            } else {
                error = CLIENT_GetLastError();
                if (error == NET_ERROR_MAC_VALIDATE_FAILED) {
                    //QMessageBox::about(this, QObject::tr("Prompt"), QObject::tr("Login failed! bad mac address"));
                } else if (error == NET_ERROR_SENIOR_VALIDATE_FAILED) {
//                    QMessageBox::about(this, QObject::tr("Prompt"),
//                                       QObject::tr("Login failed! senior validate failed"));
                }
            }
        }
        else{
            std::cout << "Login sucessful " << std::endl;
        }
    }
    else{
        std::cout << "Login sucessful " << std::endl;
    }
}
