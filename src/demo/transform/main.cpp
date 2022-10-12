#include <iostream>
#include <Eigen/Core>
#include <Eigen/Geometry>
using namespace std;
using namespace Eigen;
// let word coordination system W, objects coordination system R1,R2, we have q1,q2,t1,t2, and PR1 
// under object1's coordination system, solve P under object2's system
// PR2=TR2W*TWR1*PR1=TR2W*TR1W'*PR1
int main(){
    Quaterniond q1(0.35,0.2,0.3,0.1),q2(-0.5,0.4,-0.1,0.2);
    q1.normalize();
    q2.normalize(); // normalization => let length=1
    Vector3d t1(0.3,0.1,0.1),t2(-0.1,0.5,0.3);
    Vector3d p1(0.5,0,0.2);
    
    Isometry3d T1w(q1),T2w(q2);
    T1w.pretranslate(t1);
    T2w.pretranslate(t2);
    
    Vector3d p2=T2w*T1w.inverse()*p1;
    cout<<p2.transpose()<<endl;
    return 0;
}
