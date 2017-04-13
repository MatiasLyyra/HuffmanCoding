include_directories(${gtest_SOURCE_DIR}/include ${gtest_SOURCE_DIR})
include_directories(${CMAKE_SOURCE_DIR})
add_executable(runHuffmanTests
        HuffmanTreeTest.cpp TreeNodeTest.cpp EncoderTest.cpp TestUtils.cpp TestUtils.h DecoderTest.cpp FileUtilsTest.cpp VectorTest.cpp BitStackTest.cpp PriorityQueueTest.cpp)

target_link_libraries(runHuffmanTests gtest gtest_main)
target_link_libraries(runHuffmanTests Huffman)
target_link_libraries(runHuffmanTests Common)