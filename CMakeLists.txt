cmake_minimum_required(VERSION 3.5)
project(opengc VERSION 0.0.1 DESCRIPTION "Modernized Glass Cockpit library")

set(CMAKE_CXX_STANDARD 11)

# external modules
add_subdirectory(ext/tinyjpeg)
add_subdirectory(ext/libshape)

# glass-cockpit modules
add_subdirectory(src/config)
add_subdirectory(src/data)
add_subdirectory(src/font)
add_subdirectory(src/gauge)
add_subdirectory(src/navigation)

include_directories(
  /usr/include/libxml2
  /usr/include/FTGL
  /usr/include/freetype2
  ext/tinyjpeg
  ext/libshape
  src/config
  src/data
  src/font
  src/gauge
  src/navigation
  src/util
)

link_directories(
  /usr/lib/x86_64-linux-gnu
  ext/tinyjpeg
  ext/libshape
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
