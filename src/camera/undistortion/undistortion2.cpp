#include <iostream>
#include <cmath>
#include <opencv2/core/core.hpp>
#include <opencv2/opencv.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>


int main() {
    double k1 = -0.28340811, k2 = 0.07395907, p1 = 0.00019359, p2 = 1.76187114e-05;
    double fx = 458.654, fy = 457.296, cx = 367.215, cy = 248.375;
    cv::Mat image = cv::imread("../src/camera/undistortion/distorted.png", 0);
    int rows = image.rows, cols = image.cols;
    cv::Mat distorted_img = cv::Mat(rows, cols, CV_8UC1);
    cv::Mat camera_matrix = (cv::Mat_<double>(3, 3) << fx, 0, cx, 0, fy, cy, 0, 0, 1);
    cv::Vec4d diff_coef(k1, k2, p1, p2);

    std::cout<<camera_matrix<<std::endl;
    std::cout<<diff_coef<<std::endl;

    cv::undistort(image, distorted_img, camera_matrix,diff_coef);

    cv::imshow("src", image);
    cv::imshow("distorted", distorted_img);
    cv::imwrite("../src/camera/undistortion/res2.jpg", distorted_img);
    cv::waitKey(0);
    return 0;
}

