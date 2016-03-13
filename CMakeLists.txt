cmake_minimum_required(VERSION 2.8.9)
project (lispy)

set(EXECUTABLE_OUTPUT_PATH ${CMAKE_BINARY_DIR}/bin)

set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -g -std=c99 -Wall -Wextra")
file(GLOB SOURCES "*.c")
include_directories(".")

add_executable(lispy ${SOURCES})
target_link_libraries(lispy edit m)
