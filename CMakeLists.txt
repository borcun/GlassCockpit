cmake_minimum_required(VERSION 3.5)
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
)
