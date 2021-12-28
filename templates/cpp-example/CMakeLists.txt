cmake_minimum_required(VERSION 3.16)

project($NAME)

# Set output directory
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/bin)

file(GLOB SRC_FILES
    ${CMAKE_CURRENT_SOURCE_DIR}/source/*.cpp
)

add_executable($NAME ${SRC_FILES})

target_include_directories($NAME PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}/include
)