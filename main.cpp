#include <iostream>
#include <cstring>
#include <chrono>

#include "huffman/HuffmanTree.h"
#include "huffman/TreeNode.h"
#include "huffman/io/FileUtils.h"
#include "huffman/Encoder.h"
#include "huffman/Decoder.h"

int main() {
    /*
    auto start = std::chrono::high_resolution_clock::now();
    std::vector<huffman::types::byte_t> characters = huffman::io::readFile("C:\\Projects\\small.txt");
    huffman::HuffmanTree huffmanTree{characters};
    huffmanTree.printTree(std::cout);
    huffman::types::encode_table_t encode_table = huffmanTree.constructEncodingTable();
    huffman::Encoder encoder{"big.pack"};
    encoder.createHeader(*huffmanTree.getRoot());
    encoder.encodeData(encode_table, characters);
    huffman::Decoder decoder{"big.pack"};
    std::vector<huffman::types::byte_t> decodedData = decoder.decode();
    huffman::io::writeFile("Unpacked.txt", decodedData);
    auto finish = std::chrono::high_resolution_clock::now();
    std::cout << std::chrono::duration_cast<std::chrono::milliseconds>(finish-start).count() << " ms" << std::endl;
    std::cin.ignore();
     */
    return 0;
}

