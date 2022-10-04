#include <iostream>
#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>
using namespace std;
using namespace cv;

int main(){
    Mat src= imread("../src/binarization/origin.png");
    cout<<src.channels()<<endl;
    // 3 channels => 1 channel
    Mat grey;
    cvtColor(src,grey,COLOR_BGR2GRAY);
    cout<<grey.channels()<<endl;
    cout<<grey.type()<<endl;
    // binarization
    
    Mat binarization;
    threshold(grey,binarization,100,255,THRESH_BINARY);
    imwrite("../src/binarization/res1.png",binarization);
    // use OTSU-algorithm to solve picture with changing environment
    //threshold-val is invalid now
    threshold(grey,binarization,100,255,THRESH_OTSU);
    imwrite("../src/binarization/res-otsu.png",binarization);
    return 0;
}

