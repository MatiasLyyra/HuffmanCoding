#include "Encoder.h"

#include <cassert>

#include "io/FileUtils.h"
#include "TreeNode.h"

namespace
{
    void insertByte(huffman::types::byte_t byte, std::vector<bool>& vector)
    {
        for (int i = 0; i < huffman::constants::BITS_IN_BYTE; ++i)
        {
            huffman::types::byte_t mask = static_cast<huffman::types::byte_t>(1 << huffman::constants::BITS_IN_BYTE - 1 - i);
            vector.push_back((byte & mask) != 0);
        }
    }

    void writeTreeInBinary(const huffman::TreeNode& root, std::vector<bool>& treeInBinary)
    {
        if (root.isLeaf())
        {
            treeInBinary.push_back(true);
            insertByte(root.getData(), treeInBinary);
        }
        else
        {
            treeInBinary.push_back(false);
            writeTreeInBinary(*root.getLeftChild(), treeInBinary);
            writeTreeInBinary(*root.getRightChild(), treeInBinary);
        }
    }
}

huffman::Encoder::Encoder(const std::string& fileName) : filename_(fileName)
{
}

void huffman::Encoder::encodeData(const huffman::types::encode_table_t &encode_table, const std::vector<types::byte_t>& data)
{
    static_assert(encode_table.size() == constants::CHARACTERS);
    std::vector<bool> encodedData;
    for (auto byte : data)
    {
        types::encode_entry_t encode_entry = encode_table[byte];
        uint32_t code = encode_entry.first;
        uint8_t length = encode_entry.second;
        for (uint8_t i = 0; i < length; ++i)
        {
            int shiftAmount = length - 1 - i;
            uint32_t bit = (code & (1 << shiftAmount)) >> shiftAmount;
            encodedData.push_back(bit == 1);
        }
    }
    io::writeBinaryFile(filename_.c_str(), encodedData, true);
}

void huffman::Encoder::createHeader(const huffman::TreeNode& root)
{
    std::vector<bool> treeInBinary;
    writeTreeInBinary(root, treeInBinary);
    io::writeBinaryFile(filename_.c_str(), treeInBinary);
}



