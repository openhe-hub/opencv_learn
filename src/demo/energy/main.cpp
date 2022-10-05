#include <iostream>
#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>

//normalization tutorial: https://blog.csdn.net/page190017/article/details/90177511

int main(){
    cv::Mat src= cv::imread("../src/demo/energy/energy.png");
    assert(src.channels()==3);
    // split color channels,[0]=>blue,[1]=>green,[2]=>red
    cv::Mat channels[3];
    cv::split(src,channels);
    cv::Mat red_sub_blue=channels[2]-channels[0];
    // normalization
    // cv::NORM_MINMAX: p=ai/(max(ai)-min(ai))*|alpha-beta|+min(alpha-beta)
    cv::Mat normal_mat;
    cv::normalize(red_sub_blue,normal_mat,0,255,cv::NORM_MINMAX); //=>[0,255]
    // binarization
    cv::Mat result;
    cv::threshold(normal_mat,result,100,255,cv::THRESH_OTSU); //otsu-method
    cv::imwrite("../src/demo/energy/energy-output.jpg",result);
    return 0;
}

