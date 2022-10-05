#include <iostream>
#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>

int main() {
    cv::Mat src = cv::imread("../src/extract/energy.png");
    assert(src.channels() == 3);
    //rgb=>hsv
    cv::Mat hsv;
    cv::cvtColor(src, hsv, cv::COLOR_RGB2HSV);
    //hsv-extract
    cv::Mat hsv_part1, hsv_part2,hsv_part3;
    cv::inRange(hsv, cv::Scalar(0, 43, 46), cv::Scalar(25, 255, 255), hsv_part1);
    cv::inRange(hsv, cv::Scalar(156, 43, 46), cv::Scalar(180, 255, 255), hsv_part2);
    cv::inRange(hsv,cv::Scalar(100,43,46),cv::Scalar(124,255,255),hsv_part3);
    //combine
    cv::Mat one_mat=cv::Mat::ones(cv::Size(src.cols,src.rows),CV_8UC1);
    cv::Mat hsv_result=255*(one_mat-(one_mat-hsv_part1/255).mul(one_mat-hsv_part2/255));
    cv::imwrite("../src/extract/energy-output.jpg",hsv_result);
    cv::imwrite("../src/extract/energy-output-1.jpg",hsv_part1);
    cv::imwrite("../src/extract/energy-output-2.jpg",hsv_part2);
    cv::imwrite("../src/extract/energy-output-3.jpg",hsv_part3);
    return 0;
}

