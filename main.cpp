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
    std::vector<unsigned char> characters = huffman::io::readFile("C:\\Projects\\");
    huffmanTree.constructTree(characters);
    huffmanTree.printTree(std::cout);
    huffman::types::encode_table_t encode_table = huffmanTree.constructEncodingTable();
    huffman::Encoder encoder;
    encoder.encodeData(encode_table, characters);
    auto finish = std::chrono::high_resolution_clock::now();
    std::cout << std::chrono::duration_cast<std::chrono::nanoseconds>(finish-start).count() << "ns\n" << std::endl;
    std::cin.ignore();
    return 0;
}

