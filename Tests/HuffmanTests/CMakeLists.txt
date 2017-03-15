include_directories(${gtest_SOURCE_DIR}/include ${gtest_SOURCE_DIR})
include_directories(${CMAKE_SOURCE_DIR})
add_executable(runHuffmanTests
        HuffmanTreeTest.cpp)

target_link_libraries(runHuffmanTests Huffman)
target_link_libraries(runHuffmanTests gtest gtest_main)
target_link_libraries(runHuffmanTests Huffman)