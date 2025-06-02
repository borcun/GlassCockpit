cmake_minimum_required(VERSION 3.5)
project(opengc-sample)

set(SOURCE Main.cpp AppObject.cpp FLTKRendererWindow.cpp)

add_executable(${PROJECT_NAME} ${SOURCE})

target_include_directories(${PROJECT_NAME} PUBLIC
  ../Source/Base
  ../Source/DataSources
  ../Source/Gauges
  ../Source/Navigation
)
