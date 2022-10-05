#include <iostream>
#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>

//normalization tutorial: https://blog.csdn.net/page190017/article/details/90177511

int main(){
    cv::Mat src= cv::imread("../src/demo/energy/energy.png");
    assert(src.channels()==3);
    // 1. convert
    cv::Mat hsv;
    cv::cvtColor(src,hsv,cv::COLOR_RGB2HSV);

    cv::Mat hsv_result;
    cv::inRange(hsv,cv::Scalar(100,43,46),cv::Scalar(124,255,255),hsv_result);
    cv::imshow("extract result",hsv_result);
    cv::waitKey(0);
    return 0;

}

