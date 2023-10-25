cmake_minimum_required (VERSION 2.8) # CMake最低版本要求
set(CMAKE_CXX_STANDARD 17) # C++标准
project (RayTracing)	# 项目名称（涉及到后面的可执行文件名、链接）

aux_source_directory(. DIR_SRCS) # 根目录代码
add_executable(RayTracing ${DIR_SRCS}) # 生成可执行文件

target_compile_options(RayTracing PUBLIC -Wall -Wextra -pedantic -Wshadow -Wreturn-type -fsanitize=undefined)
target_compile_features(RayTracing PUBLIC cxx_std_17)
target_link_libraries(RayTracing PUBLIC -fsanitize=undefined)

