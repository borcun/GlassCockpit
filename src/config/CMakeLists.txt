cmake_minimum_required(VERSION 3.15)
project(opengc_config)

file(GLOB SOURCES *.cpp)

add_library(${PROJECT_NAME} SHARED ${SOURCES})

target_include_directories(${PROJECT_NAME} PUBLIC
  ../../include/util
  ../../include/config
  ../../externals/libxml2/include
)
