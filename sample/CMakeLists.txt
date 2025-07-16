cmake_minimum_required(VERSION 3.15)
project(opengc-sample)

set(CMAKE_CXX_STANDARD 11)

add_executable(${PROJECT_NAME}
  AppObject.cpp
  FLTKRenderWindow.cpp
  main.cpp
)

target_include_directories(${PROJECT_NAME} PUBLIC
  /usr/include/FL
  ../include/util
  ../include/config
  ../include/data
  ../include/font
  ../include/gauge
  ../include/navigation
  ../externals/libxml2/include
  ../externals/ftgl/src
  ../externals/freetype/include
  ../externals/tinyjpeg
)

target_link_directories(${PROJECT_NAME} PUBLIC
  /usr/lib/x86_64-linux-gnu
  src/config
  src/font
  src/data
  src/gauge
  src/navigation
)

target_link_libraries(${PROJECT_NAME} PUBLIC
  fltk
  fltk_gl
  GL
  GLU
  m
  opengc_config
  opengc_data
  opengc_gauge
  opengc_font
  opengc_navigation
  opengc
)
