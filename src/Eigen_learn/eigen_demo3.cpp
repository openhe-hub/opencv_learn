#include <iostream>
#include <Eigen/Dense>
using namespace std;
using namespace Eigen;

int main(){
    Eigen::MatrixXd m(4, 4);
    // 初始化m矩阵
    for (int i = 0; i < 4; ++i) {
        for (int j = 0; j < 4; ++j) {
            m(i, j) = j + 1 + i * 4;
        }
    }
    cout << "m: " << endl << m << endl;
    cout << "Block in the middle" << endl;
    cout << m.block<2, 2>(1, 1) << endl << endl;      // m.block<i,j> (a,b) 表示从第(a+1)行(b+1)列开始,截图i行,j列
    for (int i = 1; i <= 3; ++i) {
        cout << "Block of size " << i << "x" << i << endl;
        cout << m.block(0, 0, i, i) << endl << endl;  //m.block(a,b,i,j) 表示从第(a+1)行(b+1)列开始,截图i行,j列
    }
    cout<<"=================="<<endl;
    MatrixXd mat(2,2);
    mat<<1,2,3,4;
    m.block<2,2>(1,1) = mat;
    cout<<m<<endl;
    return 0;
}
