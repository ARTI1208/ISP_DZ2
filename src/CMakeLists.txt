cmake_minimum_required(VERSION 3.17)
project(ISP_DZ3)

set(CMAKE_CXX_STANDARD 20)

add_executable(executable main.cpp unbreakable_stack.h)

target_compile_options(executable PRIVATE -Wall -Wextra)