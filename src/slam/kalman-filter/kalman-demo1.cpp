#include <iostream>
#include <fstream>
#include <opencv2/core/core.hpp>
#include <opencv2/opencv.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <Eigen/Dense>


int main() {
    //generate data
    const int N = 20;
    const double k = 2.5;
    Eigen::Matrix<double, 1, N> noise = Eigen::Matrix<double, 1, N>::Random();
    Eigen::Matrix<double, 1, N> data = Eigen::Matrix<double, 1, N>::LinSpaced(0, k * (N - 1));
    data += noise;
    std::cout << data << std::endl;

    //calculate velocity
    const int Z_N=1,X_N=2;
    Eigen::Matrix<double,X_N,1> X;   //状态数据
    Eigen::Matrix<double,X_N,X_N> A; //状态转移矩阵
    Eigen::Matrix<double,X_N,X_N> P; //预测噪声协方差
    Eigen::Matrix<double,X_N,X_N> R; //预测过程噪声偏差的协方差
    Eigen::Matrix<double,X_N,Z_N> K; //卡尔曼增益
    Eigen::Matrix<double,Z_N,X_N> C; //观测矩阵
    Eigen::Matrix<double,Z_N,Z_N> Q; //测量噪声协方差

    X<<data[0],0;
    A<<1,1,0,1;
    C<<1,0;
    R<<2,0,0,2;
    Q<<10;

    std::ofstream ofs(R"(../src/slam/kalman-filter/out/kalman1.txt)");

    for (int i = 1; i < N; ++i) {
        //更新预测
        Eigen::Matrix<double,X_N,1> X_k=A*X;
        P=A*P*A.transpose()+R;
        //更新观测
        K=P*C.transpose()*(C*P*C.transpose()+Q).inverse();
        Eigen::Matrix<double,Z_N,1> Z{data[i]};
        X=X_k+K*(Z-C*X_k);
        P=(Eigen::Matrix<double,X_N,X_N>::Identity()-K*C)*P;
        std::cout<<"step "<<i<<":"<<X(1)<<std::endl;
        ofs<<X(1)<<std::endl;
    }
    std::cout<<"final velocity="<<X(1)<<std::endl;
}
