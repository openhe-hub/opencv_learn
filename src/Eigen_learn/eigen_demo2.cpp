#include <iostream>
#include <Eigen/Dense>

using namespace std;
using namespace Eigen;

int main() {
    Matrix2d a;
    a << 1, 2,
            3, 4;
    Matrix2d b;
    b << 4, 3,
            2, 1;
    cout << a + b << endl;
    cout << a - b << endl;
    a+=b;
    cout<<a<<endl;
    cout<<a*b<<endl;
    
    cout<<"=================="<<endl;
    cout<<a.size()<<endl;
    cout<<a.cols()<<endl;
    cout<<a.rows()<<endl;

    cout<<"=================="<<endl;
    cout<<a.determinant()<<endl;
    cout<<a.sum()<<endl;
    cout<<a.prod()<<endl;
    cout<<a.sum()<<endl;
    cout<<a.mean()<<endl;
    cout<<a.minCoeff()<<endl;
    cout<<a.maxCoeff()<<endl;
    cout<<a.trace()<<endl;
    cout<<a.inverse()<<endl;

    cout<<"=================="<<endl;
    MatrixXd mat=MatrixXd::Identity(2,2);
    cout<<mat<<endl;
    mat.resize(3,3);
    cout<<mat<<endl;

    cout<<"=================="<<endl;
    Vector3d v(1,2,3);
    Vector3d w(0,1,2);
    cout << "Dot product: " << v.dot(w) << endl;
    double dp = v.adjoint()*w; // automatic conversion of the inner product to a scalar
    cout << "Dot product via a matrix product: " << dp << endl;
    cout << "Cross product:\n" << v.cross(w) << endl;
    
    return 0;
}
