#include <iostream>
#include <cstring>
#include <chrono>

#include "huffman/HuffmanTree.h"
#include "huffman/TreeNode.h"
#include "huffman/io/FileUtils.h"
#include "huffman/Encoder.h"

int main() {
    huffman::HuffmanTree huffmanTree;
    auto start = std::chrono::high_resolution_clock::now();
    std::vector<huffman::types::byte_t> characters = huffman::io::readFile("C:\\Projects\\big.txt");
    huffmanTree.constructTree(characters);
    huffmanTree.printTree(std::cout);
    huffman::types::encode_table_t encode_table = huffmanTree.constructEncodingTable();
    huffman::Encoder encoder{"big.pack"};
    encoder.encodeData(encode_table, characters);
    auto finish = std::chrono::high_resolution_clock::now();
    std::cout << std::chrono::duration_cast<std::chrono::milliseconds>(finish-start).count() << " ms\n" << std::endl;
    std::cin.ignore();
    return 0;
}

