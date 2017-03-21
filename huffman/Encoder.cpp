#include "Encoder.h"

#include <cassert>

#include "io/FileUtils.h"
#include "TreeNode.h"

namespace
{
    uint64_t writeTreeInBinary(const huffman::TreeNode& root, huffman::io::FileBuffer& fileBuffer)
    {
        if (root.isLeaf())
        {
            fileBuffer.writeBitToBuffer(1, 0);
            fileBuffer.writeToBuffer(root.getData());
            return 1 + huffman::constants::BITS_IN_BYTE;
        }
        else
        {
            uint64_t lenghtInBits = 1;
            fileBuffer.writeBitToBuffer(0, 0);
            lenghtInBits += writeTreeInBinary(*root.getLeftChild(), fileBuffer);
            lenghtInBits += writeTreeInBinary(*root.getRightChild(), fileBuffer);
            return lenghtInBits;
        }
    }
}

huffman::Encoder::Encoder(const std::string& fileName) : filename_(fileName)
{
}

void huffman::Encoder::encodeData(const huffman::types::encode_table_t &encode_table, const std::vector<types::byte_t>& data)
{
    assert(encode_table.size() == constants::CHARACTERS);
    //TODO: Add code that writes the header here
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
    io::writeBinaryFile(filename_.c_str(), encodedData);
}

void huffman::Encoder::createHeader(const huffman::TreeNode &root)
{
    /*fileBuffer_.writeToBuffer(static_cast<uint64_t>(0));
    uint64_t lenghtInBits = writeTreeInBinary(root, fileBuffer_);
    fileBuffer_*/
}



