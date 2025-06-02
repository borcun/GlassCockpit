cmake_minimum_required(VERSION 3.5)
project(opengc-data)

set(CMAKE_CXX_STANDARD 11)

file(GLOB_RECURSE SOURCES CONFIGURE_DEPENDS *.cpp)

add_library(${PROJECT_NAME} STATIC ${SOURCES})

target_include_directories(${PROJECT_NAME} PUBLIC
  .
  ../Base
  ../Navigation
  ../../Util
)
