cmake_minimum_required(VERSION 3.14)
project(SafeSTL)

set(CMAKE_CXX_STANDARD 17)

add_library(SafeSTL STATIC Includes/SafeVector.hpp Includes/SafeMap.hpp Includes/SafeList.hpp Includes/SafeQueue.hpp main.cpp)