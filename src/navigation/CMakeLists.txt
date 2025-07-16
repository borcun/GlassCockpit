cmake_minimum_required(VERSION 3.12)
project(opengc-navigation)

set(CMAKE_CXX_STANDARD 11)

file(GLOB SOURCES *.cpp)

add_library(${PROJECT_NAME} SHARED ${SOURCES})

target_link_directories(${PROJECT_NAME} PUBLIC
  /usr/lib/x86_64-linux-gnu
  ../../externals/libshape
)

target_link_libraries(${PROJECT_NAME} PUBLIC
  shape
  xml2
  ftgl
  freetype
)
