project(HuffmanCodingApp)

if (CMAKE_BUILD_TYPE STREQUAL "coverage")
    message("Running with coverage")
    set(COMPILE_FLAGS "${COMPILE_FLAGS} -g -O0 -fprofile-arcs -ftest-coverage")
    include(CodeCoverage)
    set(LCOV_REMOVE_EXTRA "'Tests/*'")
    setup_target_for_coverage(HuffmanCoverage runHuffmanTests coverage)
endif()

set(COMPILE_FLAGS "${COMPILE_FLAGS} -Wall -Wextra -Werror -m64")
set(LINK_FLAGS    "-static")
set(CMAKE_CXX_FLAGS  "${CMAKE_CXX_FLAGS} ${COMPILE_FLAGS}" )
set(CMAKE_EXE_LINKER_FLAGS  "${CMAKE_EXE_LINKER_FLAGS} ${LINK_FLAGS}" )

set(SOURCE_FILES main.cpp)
add_executable(HuffmanCoding ${SOURCE_FILES})
target_link_libraries(HuffmanCoding Huffman)