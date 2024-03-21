cmake_minimum_required(VERSION 3.5)

project(MAIN CXX)

find_package(OpenMP)

add_executable(main main.cpp)

target_link_libraries(main PRIVATE OpenMP::OpenMP_CXX)
