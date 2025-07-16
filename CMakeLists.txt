cmake_minimum_required(VERSION 3.15)
project(opengc VERSION 0.0.1 DESCRIPTION "Modernized Glass Cockpit library" LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

add_library(${PROJECT_NAME} SHARED src/version.cpp)

target_include_directories(${PROJECT_NAME} PUBLIC
  externals/freetype/include
  externals/libxml2/include
  externals/ftgl/src
  externals/tinyjpeg
  externals/libshape
  externals/zlib
  include/util
  include/config
  include/data
  include/font
  include/navigation
  include/gauge
)

target_link_directories(${PROJECT_NAME} PUBLIC
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

target_link_libraries(${PROJECT_NAME} PUBLIC
  shape
  tinyjpeg
  xml2
  ftgl
  freetype
  z
  opengc_config
  opengc_data
  opengc_font
  opengc_gauge
  opengc_navigation
)

# external modules
add_subdirectory(externals/libxml2)
add_subdirectory(externals/tinyjpeg)
add_subdirectory(externals/libshape)
add_subdirectory(externals/ftgl)
add_subdirectory(externals/freetype)
add_subdirectory(externals/zlib)
# glass-cockpit modules
add_subdirectory(src/config)
add_subdirectory(src/data)
add_subdirectory(src/font)
add_subdirectory(src/gauge)
add_subdirectory(src/navigation)
# sample
add_subdirectory(sample)
