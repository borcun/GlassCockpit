cmake_minimum_required(VERSION 3.12)
project(opengc-navigation)

set(CMAKE_CXX_STANDARD 11)

file(GLOB_RECURSE SOURCES CONFIGURE_DEPENDS *.cpp)
file(GLOB_RECURSE SHAPE_SOURCES CONFIGURE_DEPENDS ShapeLib/*.c)
add_library(${PROJECT_NAME} SHARED ${SOURCES} ${SHAPRE_SOURCES})

target_include_directories(${PROJECT_NAME} PUBLIC
  ./
  /usr/include/libxml2
  /usr/include/freetype2
  /usr/include/FTGL
  ../ShapeLib
  ../Base
  ../ImageCodecs
  ../DataSources
  ../../Util
)

target_link_directories(${PROJECT_NAME} PUBLIC
  /usr/lib/x86_64-linux-gnu
  ShapeLib
)

target_link_libraries(${PROJECT_NAME} PUBLIC
  shape
  xml2
  ftgl
  freetype
)
