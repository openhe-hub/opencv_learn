cmake_minimum_required(VERSION 3.10)
project(ocv)

set(CMAKE_CXX_STANDARD 11)

find_package( OpenCV REQUIRED )

include_directories(${OpenCV_INCLUDE_DIRS})

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