cmake_minimum_required(VERSION 3.12)
project(opengc_gauge)

file(GLOB SOURCES *.cpp)
add_library(${PROJECT_NAME} SHARED ${SOURCES})

target_include_directories(${PROJECT_NAME} PUBLIC
  ../../include/util
  ../../include/config
  ../../include/data
  ../../include/font
  ../../include/gauge
  ../../include/navigation
  ../../externals/libxml2/include
  ../../externals/ftgl/src
  ../../externals/freetype/include
)
