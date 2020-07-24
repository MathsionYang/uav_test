//
// Created by hjx on 7/23/20.//
#include "dhnetsdk.h"
#ifndef DEVINIT_BASEINIT_H
#define DEVINIT_BASEINIT_H
#include <QMessageBox>
#include <iostream>
class baseInit {
public:
    baseInit(){};

    ~baseInit(){
    CLIENT_Cleanup();//release sdk source
    }

    //init functio
    void initData(QString Ip="192.168.2.147");
    //get image frame
    void getFrame();

private:
    LLONG m_lLoginHandle;
};


#endif //DEVINIT_BASEINIT_H
