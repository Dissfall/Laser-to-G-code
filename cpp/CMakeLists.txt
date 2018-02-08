cmake_minimum_required(VERSION 3.9)
project(laserToGCode)

set(CMAKE_CXX_STANDARD 11)

add_executable(main main.cpp)

include_directories(/usr/local/include/opencv)
include_directories(/usr/local/lib/)

target_link_libraries(main opencv_calib3d opencv_core opencv_features2d opencv_flann opencv_highgui opencv_imgcodecs opencv_imgproc opencv_ml opencv_objdetect opencv_photo opencv_shape opencv_stitching opencv_superres opencv_video opencv_videoio opencv_videostab)
