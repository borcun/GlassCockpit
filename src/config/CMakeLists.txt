cmake_minimum_required(VERSION 3.12)
project(opengc-config)

set(CMAKE_CXX_STANDARD 11)

file(GLOB SOURCES *.cpp)

add_library(${PROJECT_NAME} SHARED ${SOURCES})

target_include_directories(${PROJECT_NAME} PUBLIC
  ./
  ../../ext/tinyjpeg
  ../util
  ../data
  ../navigation
  /usr/include/libxml2
  /usr/include/FTGL
  /usr/include/freetype2
)

target_link_directories(${PROJECT_NAME} PUBLIC
  /usr/lib/x86_64-linux-gnu
  ../../ext/tinyjpeg
)

target_link_libraries(${PROJECT_NAME} PUBLIC
  tinyjpeg
  xml2
  ftgl
  freetype
  z
)
