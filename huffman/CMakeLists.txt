project(Huffman)

set(huffman_source_files HuffmanTree.cpp TreeNode.cpp io/FileUtils.cpp Common.h Encoder.cpp Decoder.cpp)

include_directories(${CMAKE_SOURCE_DIR})

add_library(Huffman ${huffman_source_files})
target_link_libraries(Huffman Common)