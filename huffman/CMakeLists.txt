project(Huffman)

set(huffman_source_files HuffmanTree.cpp TreeNode.cpp io/FileUtils.cpp Common.h Encoder.cpp Decoder.cpp)

include_directories(${common_source_files})

add_library(Huffman ${huffman_source_files})
target_include_directories(Huffman PUBLIC ../huffman)
target_link_libraries(Huffman Common)