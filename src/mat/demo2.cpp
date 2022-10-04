#include <iostream>
#include <opencv2/opencv.hpp>
#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
using namespace std;
using namespace cv;

int main(){
    cv::VideoCapture capture("../src/mat/d-result-slow.mp4");
    cv::Mat src;
    while (capture.read(src)){
        cv::imshow("src",src);
        cv::waitKey(50);
    }
    return 0;
}