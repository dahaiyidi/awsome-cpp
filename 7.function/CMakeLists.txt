cmake_minimum_required(VERSION 2.8)

project(5.main)
set(SOURCES 5.main.cpp 5.source.cpp)
add_executable(5.main ${SOURCES})
target_include_directories(5.main PUBLIC ${PROJECT_SOURCE_DIR})