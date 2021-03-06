#include "TestUtils.h"

#include <huffman/HuffmanTree.h>
#include <huffman/io/FileUtils.h>


huffman::HuffmanTree testutils::createHuffmanTreeFromCharacters()
{
    std::string message = "aaaacccddeabBe";
    common::Vector<huffman::types::byte_t> characters{convertStringToByteVector(message)};
    huffman::HuffmanTree tree{characters};
    return tree;
}

huffman::HuffmanTree testutils::createHuffmanTreeFromBinary()
{
    huffman::HuffmanTree tree{getExpectedHuffmanTreeInBinary()};
    return tree;
}

common::BitStack testutils::getExpectedHuffmanTreeInBinary()
{
    common::BitStack treeInBinary;
    // Root
    treeInBinary.push_back(false);

    // 'a' Leaf
    treeInBinary.push_back(true);
    huffman::io::insertByte('a', treeInBinary);

    // Node 9
    treeInBinary.push_back(false);
    // Node 4
    treeInBinary.push_back(false);
    // Node 2
    treeInBinary.push_back(false);
    // 'B' leaf of parent Node 2
    treeInBinary.push_back(true);
    huffman::io::insertByte('B', treeInBinary);
    // 'b' leaf of parent Node 2
    treeInBinary.push_back(true);
    huffman::io::insertByte('b', treeInBinary);

    // 'd' leaf of parent Node 4
    treeInBinary.push_back(true);
    huffman::io::insertByte('d', treeInBinary);

    // Node 5
    treeInBinary.push_back(false);
    // 'e' leaf of parent Node 5
    treeInBinary.push_back(true);
    huffman::io::insertByte('e', treeInBinary);
    // 'c' leaf of parent Node 5
    treeInBinary.push_back(true);
    huffman::io::insertByte('c', treeInBinary);
    return treeInBinary;
}

common::Vector<huffman::types::byte_t> testutils::convertStringToByteVector(const std::string& string)
{
    common::Vector<huffman::types::byte_t> characters;
    common::Vector<huffman::types::byte_t>::size_type i = 0;
    for (; i < string.size(); ++i)
    {
        huffman::types::byte_t byte = static_cast<huffman::types::byte_t>(string.at(i));
        characters.push_back(byte);
    }
    return characters;
}
