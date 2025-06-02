cmake_minimum_required(VERSION 3.5)
project(opengc-base)

#set(CMAKE_CXX_STANDARD 11)
set(LIBFREETYPE /opt/homebrew/opt/freetype/)
set(LIBXML2_DIR /opt/homebrew/opt/libxml2)
set(LIBZ_DIR /opt/homebrew/opt/zlib)

file(GLOB_RECURSE SOURCES CONFIGURE_DEPENDS *.cpp ImageCodecs/*.cpp)
file(GLOB_RECURSE IMG_SOURCES CONFIGURE_DEPENDS ImageCodes/*.c)

add_library(${PROJECT_NAME} STATIC ${SOURCES} ${IMG_SOURCES})

target_compile_definitions(${PROJECT_NAME} PRIVATE USE_FREETYPE2 TARGET_RT_LITTLE_ENDIAN)

target_include_directories(${PROJECT_NAME} PUBLIC
  ./ImageCodecs
  ../DataSources
  ../Navigation
  ../../Util
  ${LIBXML2}/include
  ${LIBZ}/include
  ${LIBFREETYPE}/include/freetype2
)

target_link_directories(${PROJECT_NAME} PUBLIC
  ${LIBXML2}/lib
  ${LIBZ}/lib
  ${LIBFREETYPE}/lib
)

target_link_directories(${PROJECT_NAME} PUBLIC
  xml2
  z
)
