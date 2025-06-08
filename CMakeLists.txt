cmake_minimum_required(VERSION 3.5)
project(opengc)

set(CMAKE_CXX_STANDARD 11)

add_subdirectory(Source/ImageCodecs)
add_subdirectory(Source/ShapeLib)
add_subdirectory(Source/Base)
add_subdirectory(Source/DataSources)
add_subdirectory(Source/Gauges)
add_subdirectory(Source/Navigation)

include_directories(
  /usr/include/libxml2
  /usr/include/FTGL
  /usr/include/freetype2
  Source/ImageCodecs
  Source/ShapeLib
  Source/Base
  Source/DataSources
  Source/Gauges
  Source/Navigation
  Util
)

link_directories(
  /usr/lib/x86_64-linux-gnu
)

link_libraries(
  xml2
  ftgl
  freetype
)
