# cmake最低版本要求
cmake_minimum_required(VERSION 3.10)

# 项目名称
project(cmake_study VERSION 1.0)

# 设置c++标准
set(CMAKE_CXX_STANDARD 11)

# 编译源码生成目录
add_executable(cmake_study src/main.cpp)