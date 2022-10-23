#include <iostream>
#include <cmath>
#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>


int main(){
    double k1 = -0.28340811, k2 = 0.07395907, p1 = 0.00019359, p2 = 1.76187114e-05;
    double fx = 458.654, fy = 457.296, cx = 367.215, cy = 248.375;
    cv::Mat image=cv::imread("../src/camera/undistortion/distorted.png",0);
    int rows=image.rows,cols=image.cols;
    cv::Mat distorted_img=cv::Mat(rows,cols,CV_8UC1);

    for (int v = 0; v < rows; ++v) {
        for (int u = 0; u < cols; ++u) {
            //像素坐标系转归一化平面
            double x=(u-cx)/fx;
            double y=(v-cy)/fy;
            double r= sqrt(pow(x,2)+ pow(y,2));
            //正畸公式，一般性只需要用到泰勒展开的前两项
            double x_distorted=x*(1+k1* pow(r,2)+k2* pow(r,4))+2*p1*x*y+p2*(pow(r,2)+2* pow(x,2));
            double y_distorted=y*(1+k1* pow(r,2)+k2* pow(r,4))+2*p2*x*y+p1*(pow(r,2)+2* pow(y,2));
            double u_distorted=fx*x_distorted+cx;
            double v_distorted=fy*y_distorted+cy;
            // 转为像素坐标系
            if (u_distorted>=0&&u_distorted<cols
                &&v_distorted>=0&&v_distorted<rows){
                distorted_img.at<uchar>(v,u)=image.at<uchar>((int)v_distorted,(int)u_distorted);
            } else{
                distorted_img.at<uchar>(v,u)=0;
            }
        }
    }

    cv::imshow("src",image);
    cv::imshow("distorted",distorted_img);
    cv::imwrite("../src/camera/undistortion/res.jpg",distorted_img);
    cv::waitKey(0);
    return 0;
}

