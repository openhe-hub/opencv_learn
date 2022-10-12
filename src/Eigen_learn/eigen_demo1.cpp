#include <iostream>
#include <Eigen/Core>
#include <Eigen/Dense>
using namespace std;
using namespace Eigen;
int main(){
    // 1.
    MatrixXd mat(2,2); // define 2*2 matrix
    mat(0,0)=3;        // use mat(i,j) to visit
    mat(1,0)=2.5;
    mat(0,1)=-1;
    mat(1,1)=mat(1,0)+mat(0,1);
    cout<<mat<<endl;
    // 2.
    MatrixXd a=MatrixXd::Random(3,3); // generate random num in [-1,1]
    a=(a+MatrixXd::Constant(3,3,1))*50; // [-1,1] => [0,100]
    cout<<a<<endl;
    VectorXd vec(3); // define 3d vector
    vec<<1,2,3;
    cout<<a*vec<<endl;
    return 0;
}
