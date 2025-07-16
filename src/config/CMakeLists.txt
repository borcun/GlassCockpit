cmake_minimum_required(VERSION 3.15)
project(opengc-config)

file(GLOB SOURCES *.cpp)
add_library(${PROJECT_NAME} SHARED ${SOURCES})
