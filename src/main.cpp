#include "dahua_dev.h"
#include <iostream>

int main(int argc, char *argv[])
{
    DahuaDev dahua_dev;
    dahua_dev.InitData();
    cv::Mat image = dahua_dev.video_stream_recv_->getMat();
    return 0;
}
