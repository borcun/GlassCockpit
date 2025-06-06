cmake_minimum_required(VERSION 3.12)
project(opengc-base)

set(CMAKE_CXX_STANDARD 98)

file(GLOB_RECURSE SOURCES CONFIGURE_DEPENDS *.cpp ImageCodecs/*.cpp)
file(GLOB_RECURSE IMG_SOURCES CONFIGURE_DEPENDS ImageCodes/*.c)
add_library(${PROJECT_NAME} STATIC ${SOURCES} ${IMG_SOURCES})

target_compile_definitions(${PROJECT_NAME} PRIVATE USE_FREETYPE2 TARGET_RT_LITTLE_ENDIAN)

target_include_directories(${PROJECT_NAME} PUBLIC
  ./ImageCodecs
  ../DataSources
  ../Navigation
  ../../Util
  /opt/homebrew/opt/libxml2/include
  /opt/homebrew/opt/zlib/include
  /opt/homebrew/opt/freetype/include/freetype2
)

target_link_directories(${PROJECT_NAME} PUBLIC
  /opt/homebrew/opt/libxml2/lib
  /opt/homebrew/opt/zlib/lib
  /opt/homebrew/opt/freetype/lib
)

target_link_directories(${PROJECT_NAME} PUBLIC
  freetype
  xml2
  z
)
