#include "Encoder.h"

#include <sstream>

#include "io/FileUtils.h"
#include "TreeNode.h"

namespace
{
    void writeTreeInBinary(const huffman::TreeNode& root, std::vector<bool>& treeInBinary)
    {
        if (root.isLeaf())
        {
            treeInBinary.push_back(true);
            huffman::io::insertByte(root.getData(), treeInBinary);
        } else
        {
            treeInBinary.push_back(false);
            writeTreeInBinary(*root.getLeftChild(), treeInBinary);
            writeTreeInBinary(*root.getRightChild(), treeInBinary);
        }
    }
}

huffman::Encoder::Encoder()
        : headerData_{},
          encodedData_{}
{
}

void
huffman::Encoder::encodeData(const huffman::types::encode_table_t& encode_table, const std::vector<types::byte_t>& data)
{
    static_assert(encode_table.size() == constants::CHARACTERS);

    for (auto byte : data)
    {
        types::encode_entry_t encode_entry = encode_table[byte];
        uint32_t code = encode_entry.first;
        uint8_t length = encode_entry.second;
        if (length == 0)
        {
            encodedData_.clear();
            std::ostringstream errorMessage;
            errorMessage << "Byte " << byte << "not found in encoding table.";
            throw std::invalid_argument(errorMessage.str());
        }
        for (uint8_t i = 0; i < length; ++i)
        {
            int shiftAmount = length - 1 - i;
            uint32_t bit = (code & (1 << shiftAmount)) >> shiftAmount;
            encodedData_.push_back(bit == 1);
        }
    }
}

void huffman::Encoder::createHeader(const huffman::TreeNode& root)
{
    writeTreeInBinary(root, headerData_);
}

const std::vector<bool>& huffman::Encoder::getHeaderData() const
{
    return headerData_;
}


const std::vector<bool>& huffman::Encoder::getEncodedData() const
{
    return encodedData_;
}



