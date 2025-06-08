cmake_minimum_required(VERSION 3.5)
<<<<<<< HEAD
project(glass-cockpit)
set(SOURCES "")

list(append ${SOURCES} Source/Base/*.cpp)
list(append ${SOURCES} Source/DataSources/*.cpp)
list(append ${SOURCES} Source/Gauges/*.cpp)
list(append ${SOURCES} Source/Navigation/*.cpp)

add_library(${PROJECT_NAME} ${SOURCES})

target_include_directories(${PROJECT_NAME} PUBLIC
  Source/Base
  Source/DataSources
  Source/Gauges
  Source/Navigation
)

target_link_directories(${PROJECT_NAME} PUBLIC
  /usr/lib/x86_64-linux-gnu/
)

target_link_libraries(${PROJECT_NAME} PUBLIC
  fltk
  fltk_gl
  xml2
=======
project(opengc)

set(CMAKE_CXX_STANDARD 11)

add_subdirectory(src/tinyjpeg)
add_subdirectory(src/libshape)
add_subdirectory(src/base)
add_subdirectory(src/data)
add_subdirectory(src/gauge)
add_subdirectory(src/navigation)

include_directories(
  /usr/include/libxml2
  /usr/include/FTGL
  /usr/include/freetype2
  src/tinyjpeg
  src/libshape
  src/base
  src/data
  src/gauge
  src/navigation
  src/util
)

link_directories(
  /usr/lib/x86_64-linux-gnu
)

link_libraries(
  xml2
  ftgl
  freetype
>>>>>>> origin/cmake-version
)
