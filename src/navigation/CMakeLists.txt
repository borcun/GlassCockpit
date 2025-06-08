cmake_minimum_required(VERSION 3.12)
project(opengc-navigation)

set(CMAKE_CXX_STANDARD 11)

file(GLOB SOURCES *.cpp)

add_library(${PROJECT_NAME} SHARED ${SOURCES})

# referring own directory is due to circular dependency, will be solved
target_include_directories(${PROJECT_NAME} PUBLIC
  ./
  ../tinyjpeg
  ../libshape
  ../util
  ../base
  ../data
  /usr/include/libxml2
  /usr/include/freetype2
  /usr/include/FTGL
)

target_link_directories(${PROJECT_NAME} PUBLIC
  /usr/lib/x86_64-linux-gnu
  libshape
)

target_link_libraries(${PROJECT_NAME} PUBLIC
  shape
  xml2
  ftgl
  freetype
)
