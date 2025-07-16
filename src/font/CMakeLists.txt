cmake_minimum_required(VERSION 3.12)
project(opengc-font)

file(GLOB SOURCES *.cpp)
add_library(${PROJECT_NAME} SHARED ${SOURCES})
target_compile_definitions(${PROJECT_NAME} PRIVATE USE_FREETYPE2 TARGET_RT_LITTLE_ENDIAN)
