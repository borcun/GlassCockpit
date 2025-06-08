cmake_minimum_required(VERSION 3.12)
project(shape)

set(CMAKE_CXX_STANDARD 11)

file(GLOB SOURCES *.c)
add_library(${PROJECT_NAME} SHARED ${SOURCES})
