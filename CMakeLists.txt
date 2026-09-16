
# CMakeLists.txt

cmake_minimum_required(VERSION 3.31)
project("GEP")

# Ensure the runtime executable and library files are outputted to the same directory
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/$<CONFIG>")
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/$<CONFIG>")

add_subdirectory("vendor")
add_subdirectory("src")