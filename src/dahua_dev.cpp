//
// Created by hjx on 7/23/20.
//

#include "dahua_dev.h"

void CALLBACK DahuaDev::DisConnectFunc(LLONG lLoginID,char *pchDVRIP, LONG nDVRPort, LDWORD dwUser){

    std::cout << "Receive disconnect message, where ip:" << pchDVRIP <<
              " and port:" << nDVRPort << " and login handle:" << lLoginID <<
              std::endl;

};

void CALLBACK DahuaDev::HaveReConnectFunc(LLONG lLoginID, char *pchDVRIP, LONG nDVRPort, LDWORD dwUser)
{
    DahuaDev* user = (DahuaDev*) dwUser;
    std::cout << "Device reconnect" << std::endl;
    if((user->login_handler_ = lLoginID)) std::cout << "Device reconnect success" << std::endl;
    return;
}

void CALLBACK DahuaDev::RealDataCallBackEx(LLONG lRealHandle, DWORD dwDataType, BYTE *pBuffer, DWORD dwBufSize, LLONG param, LDWORD dwUser)
{
    // call decoding function
    //std::cout << "dwDataType" << dwDataType << std::endl;

    DahuaDev* user = (DahuaDev*) dwUser;
//    fwrite(pBuffer+24,1,dwBufSize-32,user->file_record);
//    fwrite(pBuffer,1,dwBufSize,user->file_record);
    std::vector<uint8_t> buf;
//    CLIENT_SaveRealData(lRealHandle,user->file_record_sdk);
    if(dwDataType == 0) {
//        //std::cout << "catch" << std::endl;
        for (int i = 24; i < dwBufSize-8; i++)
            buf.push_back(pBuffer[i]);
        //std::cout<<(int)dwBufSize<<std::endl;
//        for (int i=dwBufSize-4;i<dwBufSize;i++)
//            std::cout<<std::hex<<(int)pBuffer[i]<<" ";
        //std::cout<<std::oct<<std::endl;
        user->video_stream_recv_->saveToBuffer(buf);
    }
    // std::cout << "receive real data, param: lRealHandle[%p], dwDataType[%d], pBuffer[%p], dwBufSize[%d]\n" ;
}

void DahuaDev::InitData(std::string ip) {
    std::cout << "Start to initialize data" << std::endl;
    CLIENT_Init(DisConnectFunc,(LDWORD)this);
    CLIENT_SetAutoReconnect(HaveReConnectFunc,(LDWORD)this);
    login_handler_ = 0;
    char user_name[64] = "admin";
    int dev_port = 37777;
    char password[64] = "admin";
    video_stream_recv_ = new LibAV(MANUAL_IO);
    //int error = 0;
    //get number
    //bool numok;
    //long lPort = dev_port.toLong(&numok);
    //if(numok) {
        NET_IN_LOGIN_WITH_HIGHLEVEL_SECURITY st_inparam;
        memset(&st_inparam, 0, sizeof(st_inparam));
        st_inparam.dwSize = sizeof(st_inparam);
        strncpy(st_inparam.szIP, ip.c_str(), sizeof(st_inparam.szIP) - 1);
        strncpy(st_inparam.szPassword, (char *) password, sizeof(st_inparam.szPassword) - 1);
        strncpy(st_inparam.szUserName, (char *) user_name, sizeof(st_inparam.szUserName) - 1);
//        strncpy(st_inparam.szIP, (char *) strIp.toUtf8().data(), sizeof(st_inparam.szIP) - 1);
//        strncpy(st_inparam.szPassword, (char *) password.toUtf8().data(), sizeof(st_inparam.szPassword) - 1);
//        strncpy(st_inparam.szUserName, (char *) user_name.toUtf8().data(), sizeof(st_inparam.szUserName) - 1);
        //st_inparam.nPort = lPort;
        st_inparam.nPort = dev_port;
        st_inparam.emSpecCap = EM_LOGIN_SPEC_CAP_TCP;

        NET_OUT_LOGIN_WITH_HIGHLEVEL_SECURITY st_outparam;
        memset(&st_outparam, 0, sizeof(st_outparam));
        st_outparam.dwSize = sizeof(st_outparam);
        login_handler_ = CLIENT_LoginWithHighLevelSecurity(&st_inparam, &st_outparam);

        if (login_handler_ == 0) {
            std::cout << "Login failed: " << CLIENT_GetLastError() << std::endl;

        }
        else{
            std::cout << "Login sucessful " << std::endl;
            GetRawData();
            video_stream_recv_->init();
        }
}

void DahuaDev::GetRawData() {
    std::cout << "we are try to get image stream" << std::endl;
    LLONG lRealHandle = CLIENT_RealPlayEx(login_handler_, 0, NULL, DH_RType_Realplay_2);
    if (NULL == lRealHandle)
    {
        std::cout << "CLIENT_RealPlayEx: failed! Error code: %x.\n" <<  CLIENT_GetLastError() << std::endl;
    }
    else
    {
        //file_record = fopen("./file_record","wba+");
        //file_record_sdk = fopen("./file_record_sdk","wba+");
        DWORD dwFlag = REALDATA_FLAG_RAW_DATA;
        CLIENT_SetRealDataCallBackEx2(lRealHandle, &DahuaDev::RealDataCallBackEx, (LDWORD)this, dwFlag | REALDATA_FLAG_YUV_DATA | REALDATA_FLAG_DATA_WITH_FRAME_INFO);
        std::cout << "dwFlag" << std::endl;
    }
}

void DahuaDev::getFrame() {
     //cv::Mat image = video_stream_recv.getMat();

}
