cmake_minimum_required(VERSION 3.12)
project(opengc-data)

file(GLOB SOURCES *.cpp)
add_library(${PROJECT_NAME} SHARED ${SOURCES})
