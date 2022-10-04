#include <iostream>
#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>
using namespace std;
using namespace cv;

int main(){
    Mat src= imread("../src/binarization/origin2.png");
    // 3 channels => 1 channel
    Mat grey;
    cvtColor(src,grey,COLOR_BGR2GRAY);
    // binarization
    Mat binarization;
    threshold(grey,binarization,100,255,THRESH_OTSU);
    imwrite("../src/binarization/res2-otsu.png",binarization);
    adaptiveThreshold(grey,binarization,255,
                      ADAPTIVE_THRESH_GAUSSIAN_C,THRESH_BINARY,51,0);
    imwrite("../src/binarization/res2.png",binarization);
    return 0;
}

