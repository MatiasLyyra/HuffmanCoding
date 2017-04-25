#ifndef HUFFMANCODING_TESTUTILS_H
#define HUFFMANCODING_TESTUTILS_H

#include <string>

#include "huffman/Common.h"
#include "common/Vector.h"
#include "common/BitStack.h"

namespace huffman
{
    class HuffmanTree;
}

namespace testutils
{
    huffman::HuffmanTree createHuffmanTreeFromCharacters();

    huffman::HuffmanTree createHuffmanTreeFromBinary();

    common::BitStack getExpectedHuffmanTreeInBinary();

    common::Vector<huffman::types::byte_t> convertStringToByteVector(const std::string& string);
}

#endif //HUFFMANCODING_TESTUTILS_H
