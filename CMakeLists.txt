SET("OpenCV_DIR" "~/opencv-3.1.0/build")

cmake_minimum_required(VERSION 2.8)
project(HW3)
find_package(OpenCV REQUIRED)
include_directories(${OpenCV_INCLUDE_DIRS})
add_executable(h1 h1.cpp)
target_link_libraries(h1 ${OpenCV_LIBS})
