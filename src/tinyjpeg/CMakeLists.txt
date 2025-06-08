cmake_minimum_required(VERSION 3.12)
project(tinyjpeg)

set(CMAKE_CXX_STANDARD 11)

file(GLOB SOURCES "*.c" "*.cpp")
add_library(${PROJECT_NAME} SHARED ${SOURCES})
