#include <iostream>
#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>
using namespace std;

int main(){
    cv::VideoCapture capture("../src/mat/d-result-slow.mp4");
    cv::Mat src;
    capture>>src;
    assert(!src.empty());

    string output_path="../src/mat/gery.avi";
    double fps=50;
    bool isColor= false; //gery->false
    cv::Size size=cv::Size(src.cols,src.rows);
    cv::VideoWriter writer(output_path,
                           cv::VideoWriter::fourcc('M','J','P','G'),
                           fps,size, isColor);

    while (!src.empty()){
        cv::Mat output;
        cv::cvtColor(src,output,cv::COLOR_BGR2GRAY);
        writer<<output;
        capture>>src;
    }

    return 0;
}
