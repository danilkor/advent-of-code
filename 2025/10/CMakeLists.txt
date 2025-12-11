cmake_minimum_required(VERSION 4.0)
project(10)


set(CMAKE_CXX_FLAGS_DEBUG_INIT "-O0")
set(CMAKE_CXX_FLAGS_RELEASE_INIT "-O3")

file(COPY ${CMAKE_CURRENT_SOURCE_DIR}/input.txt
        DESTINATION ${CMAKE_CURRENT_BINARY_DIR})

file(COPY ${CMAKE_CURRENT_SOURCE_DIR}/example.txt
        DESTINATION ${CMAKE_CURRENT_BINARY_DIR})

set(CMAKE_CXX_STANDARD 23)
set(Z3_ROOT_DIR "${CMAKE_SOURCE_DIR}/z3-master")
include_directories(${Z3_ROOT_DIR}/src/api)
include_directories(${Z3_ROOT_DIR}/src/api/c++)
link_directories(${Z3_ROOT_DIR}/build)
add_executable(10 main.cpp)
target_link_libraries(10 z3)
