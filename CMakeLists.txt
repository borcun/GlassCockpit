cmake_minimum_required(VERSION 3.15)
project(opengc VERSION 0.0.1 DESCRIPTION "Modernized Glass Cockpit library" LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

# external modules
add_subdirectory(externals/libxml2)
add_subdirectory(externals/tinyjpeg)
add_subdirectory(externals/libshape)
add_subdirectory(externals/ftgl)

include_directories(
  /usr/include/freetype2
  externals/tinyjpeg
  externals/libshape
  externals/libxml2/include
  externals/ftgl/src
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
  #/usr/lib/x86_64-linux-gnu
  externals/tinyjpeg
  externals/libshape
  externals/libxml2
  externals/ftgl
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
