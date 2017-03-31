cmake_minimum_required(VERSION 3.5)
project(HuffmanCoding)
set(CMAKE_CXX_STANDARD 11)

add_subdirectory(common)
add_subdirectory(huffman)
add_subdirectory(app)
add_subdirectory(Tests)

set(CMAKE_MODULE_PATH ${PROJECT_SOURCE_DIR}/cmake)
if (CMAKE_BUILD_TYPE STREQUAL "coverage")
    message("Running with coverage")
    set(COMPILE_FLAGS "${COMPILE_FLAGS} -g -O0 -fprofile-arcs -ftest-coverage")
    include(CodeCoverage)
    set(LCOV_REMOVE_EXTRA "'Tests/*'")
    setup_target_for_coverage(HuffmanCoverage runHuffmanTests coverage)
endif()


set(CMAKE_MODULE_PATH ${PROJECT_SOURCE_DIR}/cmake)