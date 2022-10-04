#include <iostream>
#include<opencv2/opencv.hpp>

using namespace std;
using namespace cv;

int main() {
    Mat img = imread("/home/sjtu/code/cpp/opencv_learn/test.png");
    imshow("bbb",img);
    waitKey(0);
    return 0;
}
