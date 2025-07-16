cmake_minimum_required(VERSION 3.12)
project(opengc-gauge)

file(GLOB SOURCES *.cpp)
add_library(${PROJECT_NAME} SHARED ${SOURCES})
