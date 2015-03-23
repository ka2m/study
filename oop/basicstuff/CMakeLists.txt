cmake_minimum_required(VERSION 2.8.4)
project(oop)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

set(SOURCE_FILES
    univeristy/main.cpp
    univeristy/Accounting.h
    univeristy/Accounting.cpp
    univeristy/Student.h
    )

add_executable(oop ${SOURCE_FILES})