#include <iostream>
#include <vector>
#include <opencv2/core/core.hpp>
#include <opencv2/opencv.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/calib3d/calib3d.hpp>

bool findCorners(const cv::Mat &src, std::vector<cv::Point2f> &corners);
void drawCorners(const cv::Mat &drawer,std::vector<cv::Point2f> &corners);



int main() {
    cv::Mat src, camera_mat, distort_mat;
    std::vector<cv::Point2f> corners;
    src = cv::imread("../src/camera/pnp/chessboard.png");
    camera_mat = (cv::Mat_<float>(3, 3) << 910.2679, 0.0, 652.0687
            , 0.0, 908.9592, 513.1698
            , 0.0, 0.0, 1.0);
    distort_mat=(cv::Mat_<float>(1,5)<<0.130,-0.487,-0.0004,-0.0004,0.598);

    bool flag= findCorners(src,corners);
    if (!flag) std::cout<<"fail to find the corner point!"<<std::endl;
    else{
        std::vector<cv::Point3f> dst;
        dst.push_back({0,0,0});
        dst.push_back({10*1,0,0});
        dst.push_back({0,7*1,0});
        dst.push_back({10*1,7*1,0});
        cv::Mat rvec,tvec;
        cv::solvePnP(dst,corners,camera_mat,distort_mat,rvec,tvec);
        std::cout<<"t:"<<std::endl<<-tvec<<std::endl;

        cv::Mat drawer=src.clone();
        drawCorners(drawer,corners);
    }

    return 0;
}

bool findCorners(const cv::Mat &src, std::vector<cv::Point2f> &corners) {
    std::vector<cv::Point2f> pts;
//    corners.clear();
    bool flag = cv::findChessboardCorners(src, {11, 8}, pts);
    if (!flag) return false;
    else {
        corners.push_back(pts[0]);
        corners.push_back(pts[11 - 1]);
        corners.push_back(pts[pts.size() - 11]);
        corners.push_back(pts[pts.size() - 1]);
        return true;
    }
}

void drawCorners(const cv::Mat &drawer,std::vector<cv::Point2f> &corners){
    for (int i = 0; i < 4; ++i) {
        cv::circle(drawer,corners[i],2,{0,255,0},2);

    }
    cv::imshow("corners",drawer);
    cv::waitKey(0);
}

