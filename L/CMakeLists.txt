cmake_minimum_required(VERSION 3.0)

project(LTest)

SET(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -save-temps=obj")

add_executable(L_test L_test.c)