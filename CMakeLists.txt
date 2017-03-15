cmake_minimum_required(VERSION 3.6)
project(HuffmanCoding)

set(CMAKE_CXX_STANDARD 11)

add_subdirectory(Huffman)
add_subdirectory(Tests)
set(SOURCE_FILES main.cpp)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)
add_executable(HuffmanCoding ${SOURCE_FILES})
target_link_libraries(HuffmanCoding Huffman)