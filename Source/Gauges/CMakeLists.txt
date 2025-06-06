cmake_minimum_required(VERSION 3.12)
project(opengc-gauges)

set(CMAKE_CXX_STANDARD 98)
file(GLOB_RECURSE SOURCES CONFIGURE_DEPENDS *.cpp)

add_library(${PROJECT_NAME} STATIC ${SOURCES})

target_include_directories(${PROJECT_NAME} PUBLIC
  ../Base
  ../Base/ImageCodecs
  ../DataSources
  ../Navigation
  ../Navigation/ShapeLib
  ../../Util
)
