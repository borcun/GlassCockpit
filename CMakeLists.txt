cmake_minimum_required(VERSION 3.5)
project(opengc)

set(SOURCE Main.cpp AppObject.cpp FLTKRendererWindow.cpp)

add_executable(${PROJECT_NAME} STATIC ${SOURCE})

target_include_directories(${PROJECT_NAME} PUBLIC
  Source/Base
  Source/Base/ImageCodecs
  Source/DataSources
  Source/Gauges
  Source/Navigation
  Source/Navigation/ShapeLib
  /opt/homebrew/opt/fltk/include
  /opt/homebrew/opt/freetype2/include
)

target_link_directories(${PROJECT_NAME} PUBLIC
  
  fltk
  freetype2
)
