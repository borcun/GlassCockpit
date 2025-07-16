cmake_minimum_required(VERSION 3.15)
project(opengc-config)

set(CMAKE_CXX_STANDARD 11)

file(GLOB SOURCES *.cpp)

add_library(${PROJECT_NAME} SHARED ${SOURCES})

target_link_directories(${PROJECT_NAME} PUBLIC
  /usr/lib/x86_64-linux-gnu
  ../../externals/tinyjpeg
)

target_link_libraries(${PROJECT_NAME} PUBLIC
  tinyjpeg
  xml2
  ftgl
  freetype
  z
)
