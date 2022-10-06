#include <iostream>
#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>

void dfs(cv::Mat &drawer,
         std::vector<std::vector<cv::Point>> &contours,
         std::vector<cv::Vec4i> &hierarchy,
         int id,
         int depth);

bool judgeContourByArea(std::vector<cv::Point> &contour){
    if (cv::contourArea(contour)<=1000) return false;
    return true;
}

bool judgeContourByConvexity(std::vector<cv::Point> &contour){
    std::vector<cv::Point> hull;
    cv::convexHull(contour,hull);
    double hull_area=cv::contourArea(hull);
    double contour_area=cv::contourArea(contour);
    if (hull_area>1.5*contour_area) return true;
    else return false;
}

bool judgeContourByRect(std::vector<cv::Point> &contour){
    double rect_area,rect_length,contour_area,contour_length;
    contour_area=cv::contourArea(contour);
    contour_length=cv::arcLength(contour,true); //arcLength(contour,isClosed)

    cv::RotatedRect rect=cv::minAreaRect(contour);
    rect_area=rect.size.area();
    rect_length=rect.size.width*2+rect.size.height*2;

    if (rect_area>2*contour_area) return false;
    if (std::abs(rect_length-contour_length)/std::min(rect_length,contour_length)>0.8) return false;
    if (std::max(rect.size.width,rect.size.height)/std::min(rect.size.height,rect.size.width)>2) return false;
    return true;
}


int main() {
    cv::Mat src = cv::imread("../src/demo/energy/energy.png");
    assert(src.channels() == 3);
    // 1. convert
    cv::Mat hsv;
    cv::cvtColor(src, hsv, cv::COLOR_RGB2HSV);
    // 2. extract
    cv::Mat hsv_result;
    cv::inRange(hsv, cv::Scalar(100, 43, 46), cv::Scalar(124, 255, 255), hsv_result);
    cv::imwrite("../src/demo/energy/extract.jpg", hsv_result);
    // 3. contour-detection
    cv::Mat canny_result;
    cv::Canny(hsv_result, canny_result, 50, 100, 3);
    cv::imwrite("../src/demo/energy/canny.jpg", canny_result);
    // 4. visit contours
    std::vector<std::vector<cv::Point>> contours;
    std::vector<cv::Vec4i> hierarchy;
    cv::findContours(hsv_result, contours, hierarchy, cv::RETR_TREE, cv::CHAIN_APPROX_NONE);
    cv::Mat result = cv::Mat::zeros(cv::Size(src.cols, src.rows), CV_8UC3);
    for (int i = 0; i != -1; i = hierarchy[i][0]) {
        dfs(result,contours,hierarchy,i,0);
    }
    cv::imwrite("../src/demo/energy/contours.jpg",result);
    return 0;
}

void dfs(cv::Mat &drawer, std::vector<std::vector<cv::Point>> &contours, std::vector<cv::Vec4i> &hierarchy, int id,
         int depth) {
    if (id==-1) return;
    std::cout<<"id="<<id<<std::endl;
    std::cout<<"depth="<<depth<<std::endl;
    for (int i = 0; i < 4; ++i) {
        std::cout<<hierarchy[id][i]<<((i==3)?"\n":",");
    }

    static cv::Scalar COLOR_LIST[3]={{220,20,20},{20,220,20},{20,20,220}};
    cv::Scalar CONVEX_COLOR={20,20,220};
    cv::Scalar RECT_COLOR={290,0.82,0.87};
    if (judgeContourByArea(contours[id])){
        if (!depth && !judgeContourByConvexity(contours[id])){
            cv::drawContours(drawer,contours,id,CONVEX_COLOR,5);
        }else if (depth && judgeContourByRect(contours[id]) && !judgeContourByConvexity(contours[hierarchy[id][3]])){
            cv::drawContours(drawer,contours,id,RECT_COLOR,3);
        }else{
            cv::drawContours(drawer,contours,id,COLOR_LIST[depth%3]);
        }
    }
    for (int i=hierarchy[id][2];i!=-1;i=hierarchy[i][0]){
        dfs(drawer,contours,hierarchy,i,depth+1);
    }
}

