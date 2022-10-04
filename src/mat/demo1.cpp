#include <iostream>
#include <opencv2/opencv.hpp>

int main(){
    //1. construction
    //1.1 read from picture
    cv::Mat apple=cv::imread("../src/mat/apple.jpg");
    //std::cout<<apple<<std::endl;
    //1.2 rows,cols,types
    //CV_8UC3: 8-unsigned, 3 channels, pictures
    //CV_64FC1: 64-float, 1 channels, real numbers
    cv::Mat apple2=cv::Mat(10,20,CV_8UC3);
    //1.3 special matrices
    cv::Mat e_mat=cv::Mat::eye(4,4,CV_64F);
    cv::Mat p_mat=cv::Mat::ones(2,3,CV_32F);
    cv::Mat z_mat=cv::Mat::zeros(4,4,CV_8UC1);
    //1.4 value
    cv::Mat mat=(cv::Mat_<double>(2,3)<<1,2,3,4,5,6);
    //std::cout<<mat<<std::endl;


    //2. visit
    //2.1 at() -> Tp_ &
    cv::Mat src=cv::Mat::eye(3,3,CV_8UC1);
    std::cout<<src<<std::endl;
    src.at<uint8_t>(1,2)=static_cast<uint8_t>(2);
    std::cout<<src<<std::endl;
    //2.2 ptr() -> row pointer *
    uchar *ptr=src.ptr(0);
    ptr[2]=2;
    std::cout<<src<<std::endl;

    //3. clone
    // USE DEEP CLONE!!!
    cv::Mat a=src.clone();
    cv::Mat b=src;
    src.at<uint8_t>(2,2)=static_cast<uint8_t>(2);
//    std::cout<<"src:\n"<<src<<"\na:\n"<<a<<"\nb:\n"<<b<<std::endl;

    //4. operation
    a = cv::Mat::eye(3, 3, CV_64FC1);
    b = (cv::Mat_<double>(3, 3) << 1, 2, 3, 4, 5, 6, 7, 8, 9);
    std::cout << "a:\n" << a << std::endl << "b:\n" << b << std::endl;
    //4.1 add
    std::cout<<"a+b=\n"<<a+b<<std::endl;
    cv::Mat tmp=cv::Mat(3,3,CV_64FC1);
    cv::add(a,b,tmp);
    std::cout<<"add(a,b,tmp)=\n"<<tmp<<std::endl;
    //4.2 subtract
    std::cout<<"a-b=\n"<<a-b<<std::endl;
    cv::subtract(a,b,tmp);
    std::cout<<"subtract(a,b,tmp)=\n"<<tmp<<std::endl;
    //4.3 multiply
    std::cout<<"a*b=\n"<<a*b<<std::endl;
    cv::multiply(a,b,tmp);
    std::cout<<"multiply(a,b,tmp)=\n"<<tmp<<std::endl;

    return 0;
}