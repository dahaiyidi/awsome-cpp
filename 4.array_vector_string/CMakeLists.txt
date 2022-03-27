cmake_minimum_required(VERSION 2.8)
project(main2)
aux_source_directory(. SRC_LIST)
set(SOURCES main.cpp source.cpp)
add_executable(${PROJECT_NAME} main.cpp source.cpp)

