cmake_minimum_required(VERSION 3.12)
project(opengc-gauge)

set(CMAKE_CXX_STANDARD 11)
file(GLOB SOURCES *.cpp)

add_library(${PROJECT_NAME} SHARED ${SOURCES})

target_include_directories(${PROJECT_NAME} PUBLIC
  ../../ext/tinyjpeg
  ../../ext/libshape
  ../util
  ../config
  ../font
  ../data
  ../navigation
  /usr/include/libxml2
  /usr/include/freetype2
  /usr/include/FTGL
)

target_link_directories(${PROJECT_NAME} PUBLIC
  /usr/lib/x86_64-linux-gnu
)

target_link_libraries(${PROJECT_NAME} PUBLIC
  xml2
  ftgl
  freetype
)
