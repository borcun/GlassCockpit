cmake_minimum_required(VERSION 3.15)
project(opengc VERSION 0.0.1 DESCRIPTION "Modernized Glass Cockpit library" LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

# external modules
add_subdirectory(externals/libxml2)
add_subdirectory(externals/tinyjpeg)
add_subdirectory(externals/libshape)
add_subdirectory(externals/ftgl)
add_subdirectory(externals/freetype)
add_subdirectory(externals/zlib)

include_directories(
  externals/freetype/include
  externals/libxml2/include
  externals/ftgl/src
  externals/tinyjpeg
  externals/libshape
  externals/zlib
  include/config
  include/data
  include/font
  include/navigation
  include/gauge
  include/util
)

# glass-cockpit modules
add_subdirectory(src/config)
add_subdirectory(src/data)
add_subdirectory(src/font)
add_subdirectory(src/gauge)
add_subdirectory(src/navigation)

link_directories(
  externals/tinyjpeg
  externals/libshape
  externals/libxml2
  externals/ftgl
  externals/freetype
  externals/zlib
  src/config
  src/data
  src/font
  src/gauge
  src/navigation
)

link_libraries(
  shape
  tinyjpeg
  xml2
  ftgl
  freetype
  z
  opengc-config
  opengc-data
  opengc-font
  opengc-gauge
  opengc-navigation
)
