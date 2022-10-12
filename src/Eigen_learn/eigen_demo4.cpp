#include <iostream>
#include <Eigen/Dense>
using namespace std;
using namespace Eigen;

int main(){
    ArrayXXd arr(2,2);
    arr<<1,2,3,4;
    cout<<(arr>2).all()<<endl;
    cout<<(arr>2).any()<<endl;
    cout<<(arr>2).count()<<endl;
    return 0;
}
