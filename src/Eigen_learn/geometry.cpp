#include <iostream>
#include <Eigen/Core>
#include <Eigen/Geometry>
using namespace std;
using namespace Eigen;

int main(){
    // 1. rotation matrix & vector
    Matrix3d rotation_matrix=Matrix3d::Identity(); // rotation matrix
    AngleAxisd rotation_vector(M_PI/4,Vector3d(0,0,1));  // rotation vector, z-axis-pi/4
    cout<<"rotation matrix=\n"<<rotation_vector.matrix()<<endl;
    rotation_matrix=rotation_vector.toRotationMatrix();
    cout<<"rotation matrix=\n"<<rotation_matrix<<endl;
    // 2. rotation demo
    Vector3d vec(1,0,0);
    Vector3d vec_rotated=rotation_vector*vec;
    cout<<"rotated by rotation vector=\n"<<vec_rotated<<endl;
    vec_rotated=rotation_matrix*vec;
    cout<<"rotated by rotation matrix=\n"<<vec_rotated<<endl;
    // 3.Euler Angle
    Vector3d euler_angles=rotation_matrix.eulerAngles(2,1,0); //z,y,x <==> yaw,pitch,roll
    cout<<"yaw pitch row=\n"<<euler_angles.transpose()<<endl;
    // 4.Euler transformation
    Isometry3d T=Isometry3d::Identity();
    T.rotate(rotation_vector);
    T.pretranslate(Vector3d(1,3,4));
    cout<<"Transform matrix=\n"<<T.matrix()<<endl;
    Vector3d vec_transformed=T*vec;
    cout<<"vector transformed=\n"<<vec_transformed<<endl;
    // 5.quaternion
    Quaterniond q=Quaterniond(rotation_vector);
    cout<<"quaternion from rotation vector=\n"<<q.coeffs().transpose()<<endl; //(x,y,z,w) w is real
    vec_rotated=q*vec;
    cout<<"(1,0,0) after rotation=\n"<<vec_rotated.transpose()<<endl;

    return 0;
}
