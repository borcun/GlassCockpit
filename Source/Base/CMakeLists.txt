cmake_minimum_required(VERSION 3.12)
project(opengc-base)

set(CMAKE_CXX_STANDARD 11)

file(GLOB_RECURSE SOURCES CONFIGURE_DEPENDS *.cpp ImageCodecs/*.cpp ImageCodecs/*.c)

add_library(${PROJECT_NAME} SHARED ${SOURCES})

target_compile_definitions(${PROJECT_NAME} PRIVATE USE_FREETYPE2 TARGET_RT_LITTLE_ENDIAN)

target_include_directories(${PROJECT_NAME} PUBLIC
  ../ImageCodecs
  ../DataSources
  ../Navigation
  ../../Util
  /usr/include/libxml2
  /usr/include/FTGL
  /usr/include/freetype2
)

target_link_directories(${PROJECT_NAME} PUBLIC
  /usr/lib/x86_64-linux-gnu
  ImageCodecs
)

target_link_libraries(${PROJECT_NAME} PUBLIC
  tinyjpeg
  xml2
  ftgl
  freetype
  z
)
