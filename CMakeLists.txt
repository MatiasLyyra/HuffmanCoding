cmake_minimum_required(VERSION 3.6)
project(HuffmanCoding)
set(CMAKE_CXX_STANDARD 11)

add_subdirectory(Huffman)
add_subdirectory(Tests)

set(CMAKE_MODULE_PATH ${PROJECT_SOURCE_DIR}/cmake)
include(CodeCoverage)
setup_target_for_coverage(Huffman runHuffmanTests coverage)

set(COMPILE_FLAGS "-Wall -Wextra -m64")
set(LINK_FLAGS    "-static")
set(CMAKE_CXX_FLAGS  "${CMAKE_CXX_FLAGS} ${COMPILE_FLAGS}" )
set(CMAKE_EXE_LINKER_FLAGS  "${CMAKE_EXE_LINKER_FLAGS} ${LINK_FLAGS}" )

set(SOURCE_FILES main.cpp)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)
add_executable(HuffmanCoding ${SOURCE_FILES})
target_link_libraries(HuffmanCoding Huffman)