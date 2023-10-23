cmake_minimum_required (VERSION 2.8.11)
set(CMAKE_CXX_STANDARD 17)
project (Transformation)

aux_source_directory(. DIR_SRCS)
add_executable(Transformation ${DIR_SRCS})

# eigen
include_directories(/usr/local/Cellar/eigen/3.4.0_1/include)
add_library(eigen INTERFACE)
target_include_directories(eigen INTERFACE /usr/local/Cellar/eigen/3.4.0_1/include)
target_link_libraries(Transformation eigen)

# opencv
include_directories(/usr/local/Cellar/opencv@3/3.4.16_10/include)
file(GLOB OpenCV_LIBS /usr/local/Cellar/opencv@3/3.4.16_10/lib/*.dylib)
target_link_libraries(Transformation ${OpenCV_LIBS})