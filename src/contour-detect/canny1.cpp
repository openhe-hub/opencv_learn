#include <iostream>
#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>
using namespace std;
using namespace cv;

int main(){
    Mat src= imread("../src/extract/energy-output-3.jpg");
    Mat grey;
    cvtColor(src,grey,COLOR_BGR2GRAY);
    assert(grey.channels()==1);
    Mat canny_result;
    Canny(grey,canny_result,50,100,3);
    imwrite("../src/contour-detect/canny-res1.jpg",canny_result);
    return 0;
}

