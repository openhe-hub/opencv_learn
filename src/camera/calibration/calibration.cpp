#include <iostream>
#include <opencv2/opencv.hpp>
#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>


int main() {
    // init
    const int board_width = 11, board_height = 8;
    const int board_n = board_height * board_width;
    cv::Size board_size = {board_width, board_height};

    cv::Mat gray_img;
    std::vector<cv::Point2f> point_pix_pos_buf;
    std::vector<std::vector<cv::Point2f>> point_pix_pos;
    cv::Size img_size;

    int k = 0, n = 0, found = 0;

    cv::Mat src0 = cv::imread("../src/camera/calibration/distortion.png");
    img_size.width = src0.cols;
    img_size.height = src0.rows;

    // find corner point
    found = cv::findChessboardCorners(src0, board_size, point_pix_pos_buf);
    if (found && point_pix_pos_buf.size() == board_n) {
        cv::cvtColor(src0, gray_img, cv::COLOR_BGR2GRAY);
        cv::find4QuadCornerSubpix(gray_img, point_pix_pos_buf, cv::Size(5, 5));
        point_pix_pos.push_back(point_pix_pos_buf);

        cv::Mat drawer = src0.clone();
        cv::drawChessboardCorners(drawer, board_size, point_pix_pos_buf, found);
        cv::imwrite("../src/camera/calibration-out.jpg", drawer);
    } else {
        std::cout << "unable to find clear enough corner points.\n";
        point_pix_pos_buf.clear();
    }

    // calibration
    cv::Size square_size(10,10);
    // 相机内参
    cv::Mat  camera_matrix(3,3,CV_32FC1,cv::Scalar::all(0));
    // 畸变参数
    cv::Mat  dist_coef(1,5,CV_32FC1,cv::Scalar::all(0));
    std::vector<std::vector<cv::Point3f>> point_grid_pos;
    std::vector<cv::Point3f> point_grid_pos_buf;
    std::vector<int> point_cnt;
    std::vector< cv::Mat > rvecs;
    std::vector< cv::Mat > tvecs;


    for (int i = 0; i < board_height; ++i) {
        for (int j = 0; j < board_width; ++j) {
            cv::Point3f pt;
            pt.x=j*square_size.width;
            pt.y=i*square_size.height;
            pt.z=0;
            point_grid_pos_buf.push_back(pt);
        }
    }
    point_grid_pos.push_back(point_grid_pos_buf);
    point_cnt.push_back(board_n);

    std::cout<<cv::calibrateCamera(point_grid_pos,point_pix_pos,img_size,camera_matrix,dist_coef,rvecs,tvecs)
    <<std::endl;

    std::cout<<camera_matrix<<"\n"<<dist_coef;
    return 0;
}

