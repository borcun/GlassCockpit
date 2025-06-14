cmake_minimum_required(VERSION 3.12)
project(opengc-data)

set(CMAKE_CXX_STANDARD 11)

file(GLOB SOURCES *.cpp)
add_library(${PROJECT_NAME} SHARED ${SOURCES})

# referring own directory is due to circular dependency, will be solved
target_include_directories(${PROJECT_NAME} PUBLIC
  ./
  ../util
  ../config
  ../font
  ../navigation
  /usr/include/libxml2
  /usr/include/FTGL
  /usr/include/freetype2
)

target_link_directories(${PROJECT_NAME} PUBLIC
  /usr/lib/x86_64-linux-gnu
)

target_link_libraries(${PROJECT_NAME} PUBLIC
  xml2
  ftgl
  freetype
)
