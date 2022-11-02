#include <iostream>
#include <opencv2/core/core.hpp>
#include <opencv2/opencv.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <Eigen/Dense>


int main() {
    //generate data
    const int N = 20;
    const double K = 2.5;
    Eigen::Matrix<double, 1, N> noise = Eigen::Matrix<double, 1, N>::Random();
    Eigen::Matrix<double, 1, N> data = Eigen::Matrix<double, 1, N>::LinSpaced(0, K * (N - 1));
    data += noise;
    std::cout << data << std::endl;

    //calculate velocity
    double speed_sum = 0;
    for (int i = 1; i < N; ++i) {
        double speed = (data[i] - data[i - 1]);
        speed_sum += speed;
        std::cout << "step " << i << ":" << speed << std::endl;
    }
    std::cout << "final velocity=" << speed_sum / (N - 1) << std::endl;
    return 0;
}

