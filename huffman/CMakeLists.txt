project(Huffman)

set(huffman_source_files HuffmanTree.cpp TreeNode.cpp io/FileUtils.cpp Common.h Encoder.cpp Decoder.cpp)

add_library(Huffman ${huffman_source_files})