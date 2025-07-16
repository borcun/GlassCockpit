cmake_minimum_required(VERSION 3.12)
project(opengc_data)

file(GLOB SOURCES *.cpp)
add_library(${PROJECT_NAME} SHARED ${SOURCES})

target_include_directories(${PROJECT_NAME} PUBLIC
  ../../include/util
  ../../include/config
  ../../include/data
  ../../externals/libxml2/include
)
