cmake_minimum_required(VERSION 3.8)

project(filatov_i_a)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED True)

find_package(doctest REQUIRED)

add_subdirectory(prj.lab)
add_subdirectory(prj.test)