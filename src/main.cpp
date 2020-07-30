#include "dahua_dev.h"
#include <iostream>
#include <thread>
#include <chrono>

int main(int argc, char *argv[])
{
    DahuaDev dahua_dev;
    dahua_dev.InitData();
    std::this_thread::sleep_for(std::chrono::seconds(2));
    cv::Mat image = dahua_dev.video_stream_recv_->getMat();
    for (;;) {
        image = dahua_dev.video_stream_recv_->getMat();
        cv::imshow("image",image);
        cv::waitKey(10);
    }
    return 0;
}
