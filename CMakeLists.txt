cmake_minimum_required(VERSION 3.5)
project(HuffmanCoding)
set(CMAKE_CXX_STANDARD 11)

add_subdirectory(common)
add_subdirectory(huffman)
add_subdirectory(app)
add_subdirectory(Tests)

set(CMAKE_MODULE_PATH ${PROJECT_SOURCE_DIR}/cmake)