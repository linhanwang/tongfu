cmake_minimum_required(VERSION 3.10)
project(tongfu)

set(CMAKE_CXX_STANDARD 17)

set(default_build_type "Release")
if(EXISTS "${CMAKE_SOURCE_DIR}/.git")
    set(default_build_type "Debug")
endif()

include_directories(${PROJECT_SOURCE_DIR})

add_subdirectory(tongfu)
