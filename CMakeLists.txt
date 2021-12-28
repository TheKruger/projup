cmake_minimum_required(VERSION 3.16)

project(projup)

# Set C++20 standard
set(CMAKE_CXX_STANDARD 20)

# Set the output directory
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}/bin)

file(GLOB SRC_FILES
    ${CMAKE_CURRENT_SOURCE_DIR}/source/*.cpp
)

add_executable(projup ${SRC_FILES})

target_include_directories(projup PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}/include
)

install(TARGETS projup DESTINATION bin)