cmake_minimum_required(VERSION 3.12)
project(opengc-navigation)

set(CMAKE_CXX_STANDARD 98)

file(GLOB_RECURSE SOURCES CONFIGURE_DEPENDS *.cpp)
file(GLOB_RECURSE SHAPE_SOURCES CONFIGURE_DEPENDS ShapeLib/*.c)
add_library(${PROJECT_NAME} STATIC ${SOURCES} ${SHAPRE_SOURCES})

target_include_directories(${PROJECT_NAME} PUBLIC
  ./
  ./ShapeLib
  ../Base
  ../Base/ImageCodecs
  ../DataSources
  ../../Util
)
