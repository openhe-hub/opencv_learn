#include <iostream>
#include <string>
#include <vector>
#include <opencv2/core/core.hpp>
#include <Eigen/Dense>
#include <ceres/jet.h>

using namespace std;
using namespace cv;
using namespace Eigen;
using ceres::Jet;

// EKF类，作者：唐欣阳
//
// Created by xinyang on 2021/3/15.
//
template<int N_X, int N_Y>
class AdaptiveEKF {
    using MatrixXX = Eigen::Matrix<double, N_X, N_X>;
    using MatrixYX = Eigen::Matrix<double, N_Y, N_X>;
    using MatrixXY = Eigen::Matrix<double, N_X, N_Y>;
    using MatrixYY = Eigen::Matrix<double, N_Y, N_Y>;
    using VectorX = Eigen::Matrix<double, N_X, 1>;
    using VectorY = Eigen::Matrix<double, N_Y, 1>;
public:
    explicit AdaptiveEKF(const VectorX &X0 = VectorX::Zero())
            : Xe(X0), P(MatrixXX::Identity()), Q(MatrixXX::Identity()),
              R(MatrixYY::Identity()) {}

    template<class Func>
    VectorX predict(Func &&func) {
        ceres::Jet<double, N_X> Xe_auto_jet[N_X];
        for (int i = 0; i < N_X; i++) {
            Xe_auto_jet[i].a = Xe[i];
            Xe_auto_jet[i].v[i] = 1;
        }
        ceres::Jet<double, N_X> Xp_auto_jet[N_X];
        func(Xe_auto_jet, Xp_auto_jet);
        for (int i = 0; i < N_X; i++) {
            Xp[i] = Xp_auto_jet[i].a;
            F.block(i, 0, 1, N_X) = Xp_auto_jet[i].v.transpose();
        }
        P = F * P * F.transpose() + Q;
        return Xp;
    }

    template<class Func>
    VectorX update(Func &&func, const VectorY &Y) {
        ceres::Jet<double, N_X> Xp_auto_jet[N_X];
        for (int i = 0; i < N_X; i++) {
            Xp_auto_jet[i].a = Xp[i];
            Xp_auto_jet[i].v[i] = 1;
        }
        ceres::Jet<double, N_X> Yp_auto_jet[N_Y];
        func(Xp_auto_jet, Yp_auto_jet);
        for (int i = 0; i < N_Y; i++) {
            Yp[i] = Yp_auto_jet[i].a;
            H.block(i, 0, 1, N_X) = Yp_auto_jet[i].v.transpose();
        }
        K = P * H.transpose() * (H * P * H.transpose() + R).inverse();
        Xe = Xp + K * (Y - Yp);
        P = (MatrixXX::Identity() - K * H) * P;
        return Xe;
    }

    VectorX Xe; // 估计状态变量
    VectorX Xp; // 预测状态变量
    MatrixXX F; // 预测雅克⽐
    MatrixYX H; // 观测雅克⽐
    MatrixXX P; // 状态协⽅差 *
    MatrixXX Q; // 预测过程协⽅差 * -
    MatrixYY R; // 观测过程协⽅差 *
    MatrixXY K; // 卡尔曼增益
    VectorY Yp; // 预测观测量
};

constexpr int Z_N = 2, X_N = 3;

/**
 * x[0] : y
 * x[1] : x
 * x[2] : k
 */
struct Predict {
    template<typename T>
    void operator()(const T x0[X_N], T x1[X_N]) {
        x1[0] = x0[2] * (x0[1] + delta_x) * (x0[1] + delta_x);
        x1[1] = x0[1] + delta_x;
        x1[2] = x0[2];
    }

    double delta_x = 1;
} predict;

struct Measure {
    template<typename T>
    void operator()(const T x0[X_N], T z0[Z_N]) {
        z0[0] = x0[0];
        z0[1] = z0[1];
    }
} measure;

int main() {
    srand(0);
    // generate data with noise
    const int N = 100;
    const double k = 1;
    Matrix<double, 1, N> noise = Matrix<double, 1, N>::Random();
    Matrix<double, 1, N> data = Matrix<double, 1, N>::LinSpaced(0, k * (N
                                                                        - 1));
    data += noise;
    data = (data.array() * data.array()).matrix();
    std::cout << "a = [" << data << "]" << std::endl;
    // calculate speed
    AdaptiveEKF<X_N, Z_N> ekf;
    ekf.Q << 1, 0, 0,
            0, 1, 0,
            0, 0, 1;
    ekf.R << 1, 0, 0, 1;
    ekf.Xe << data[0], 0, 0;

    std::cout << "b = [0 ";
    for (int i = 1; i < N; i++) {
        ekf.predict(predict);
        Matrix<double, Z_N, 1> watch;
        watch << data[i], i;
        auto xe = ekf.update(measure, watch);
        std::cout << 2 * xe[1] * xe[2] << " ";
    }
    std::cout << "]";

    return 0;
}