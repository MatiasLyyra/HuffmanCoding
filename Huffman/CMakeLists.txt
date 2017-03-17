project(Huffman)

set(huffman_source_files HuffmanTree.cpp TreeNode.cpp io/FileUtils.cpp io/FileUtils.h Common.h Encoder.cpp Encoder.h)

add_library(Huffman ${huffman_source_files})