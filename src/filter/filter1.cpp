#include <iostream>
#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>
using namespace std;
using namespace cv;

// average filtering

int main(){
    Mat src= imread("../src/filter/origin.png");
    Mat blured_img;
    blur(src,blured_img,Size(7,7));
    imwrite("../src/filter/avg-filter.jpg",blured_img);
    GaussianBlur(src,blured_img,Size(7,7),0,0);
    imwrite("../src/filter/gaussian-filter.jpg",blured_img);
    medianBlur(src,blured_img,7);
    imwrite("../src/filter/mean-filter.jpg",blured_img);
    return 0;
}

