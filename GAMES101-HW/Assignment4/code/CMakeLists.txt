cmake_minimum_required(VERSION 3.10)
set(CMAKE_CXX_STANDARD 17)
project(BezierCurve)

aux_source_directory(. DIR_SRCS)
add_executable(BezierCurve ${DIR_SRCS})

# opencv
include_directories(/usr/local/Cellar/opencv@3/3.4.16_10/include)
file(GLOB OpenCV_LIBS /usr/local/Cellar/opencv@3/3.4.16_10/lib/*.dylib)
target_link_libraries(BezierCurve ${OpenCV_LIBS})
