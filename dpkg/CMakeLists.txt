# CMake 最低版本号要求
cmake_minimum_required(VERSION 3.13)
# 项目名称
project(dpkg)

set(CMAKE_BINARY_DIR "./src")

set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR})
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR})
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR})

# 指定生成目标，将main.cpp,MyMath.cpp生成一个名为demo2的可以执行文件
add_executable(pkgverify dpkg.c)

