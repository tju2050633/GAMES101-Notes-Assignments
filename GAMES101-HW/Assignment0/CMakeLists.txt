cmake_minimum_required (VERSION 2.8.11)
project (Transformation)

add_executable (Transformation main.cpp)

# eigen
include_directories(/usr/local/Cellar/eigen/3.4.0_1/include)
add_library(eigen INTERFACE)
target_include_directories(eigen INTERFACE /usr/local/Cellar/eigen/3.4.0_1/include)
target_link_libraries(Transformation eigen)