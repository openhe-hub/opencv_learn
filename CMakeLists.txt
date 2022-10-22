cmake_minimum_required(VERSION 3.10)
project(ocv)

set(CMAKE_CXX_STANDARD 11)

find_package( OpenCV REQUIRED )

include_directories(${OpenCV_INCLUDE_DIRS})
include_directories("/usr/include/eigen3")

add_executable(ocv main.cpp)
target_link_libraries(  ocv ${OpenCV_LIBS}  )


add_executable(my_test test/test.cpp)
add_executable(demo1 src/mat/demo1.cpp)
target_link_libraries(demo1 ${OpenCV_LIBS})
add_executable(demo2 src/mat/demo2.cpp)
target_link_libraries(demo2 ${OpenCV_LIBS})
add_executable(demo3 src/mat/demo3.cpp)
target_link_libraries(demo3 ${OpenCV_LIBS})

add_executable(binarization1 src/binarization/binarization1.cpp)
target_link_libraries(binarization1 ${OpenCV_LIBS})
add_executable(binarization2 src/binarization/binarization2.cpp)
target_link_libraries(binarization2 ${OpenCV_LIBS})
add_executable(energy_main src/demo/energy/main.cpp)
target_link_libraries(energy_main ${OpenCV_LIBS})
add_executable(hsv-substraction src/extract/hsv-extract.cpp)
target_link_libraries(hsv-substraction ${OpenCV_LIBS})
add_executable(filter1 src/filter/filter1.cpp)
target_link_libraries(filter1 ${OpenCV_LIBS})
add_executable(canny1 src/contour-detect/canny1.cpp)
target_link_libraries(canny1 ${OpenCV_LIBS})

add_executable(channel src/extract/channel.cpp)
target_link_libraries(channel ${OpenCV_LIBS})
add_executable(eigen_demo1 src/Eigen_learn/eigen_demo1.cpp)
add_executable(eigen_demo2 src/Eigen_learn/eigen_demo2.cpp)
add_executable(eigen_demo3 src/Eigen_learn/eigen_demo3.cpp)
add_executable(eigen_demo4 src/Eigen_learn/eigen_demo4.cpp)
add_executable(geometry src/Eigen_learn/geometry.cpp)

add_executable(transform_main src/demo/transform/main.cpp)

add_executable(calibration src/camera/calibration.cpp)
target_link_libraries(calibration ${OpenCV_LIBS})