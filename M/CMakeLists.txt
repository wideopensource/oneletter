cmake_minimum_required(VERSION 3.0)

project(MTest)

SET(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -save-temps=obj")

add_executable(M_test M_test.c)

target_include_directories(M_test PRIVATE ..)

