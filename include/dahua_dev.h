//
// Created by hjx on 7/23/20.//
#pragma once
#include "dhnetsdk.h"
#ifndef DEVINIT_BASEINIT_H
#define DEVINIT_BASEINIT_H
#include <iostream>
#include "libav.hpp"
#include <string>
#include <thread>
class DahuaDev {
public:
    DahuaDev(){
        //video_stream_recv_ = new LibAV("abc",MANUAL_IO) ;
        //std::cout << "bbb" << std::endl;
    };

    ~DahuaDev(){
        CLIENT_Cleanup();//release sdk source
    }

    static void CALLBACK RealDataCallBackEx(LLONG lRealHandle, DWORD dwDataType, BYTE *pBuffer, DWORD dwBufSize, LLONG param, LDWORD dwUser);
    static void CALLBACK  HaveReConnectFunc(LLONG lLoginID, char *pchDVRIP, LONG nDVRPort, LDWORD dwUser);
    static void CALLBACK DisConnectFunc(LLONG lLoginID,char *pchDVRIP, LONG nDVRPort, LDWORD dwUser);

    //init function
    void InitData(std::string ip="192.168.2.147");
    //get image frame
    void getFrame();
    //get raw data
    void GetRawData();
    LLONG getHandel(){return login_handler_;};

    LibAV* video_stream_recv_;


    BYTE raw_data_;
private:
    //void CALLBACK  HaveReConnectFunc(LLONG lLoginID, char *pchDVRIP, LONG nDVRPort, LDWORD dwUser);
    LLONG login_handler_;
};


#endif //DEVINIT_BASEINIT_H
