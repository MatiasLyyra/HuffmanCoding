#include "Encoder.h"

#include <sstream>
#include <cassert>

#include "io/FileUtils.h"
namespace
{
    void writeTreeInBinary(huffman::types::handle_t rootHandle, const huffman::HuffmanTree &huffmanTree, common::BitStack& treeInBinary)
    {
        const huffman::TreeNode* root = huffmanTree.getNode(rootHandle);
        if (root->isLeaf())
        {
            treeInBinary.push_back(true);
            huffman::io::insertByte(root->getData(), treeInBinary);
        } else
        {
            treeInBinary.push_back(false);
            writeTreeInBinary(root->getLeftChildHandle(), huffmanTree, treeInBinary);
            writeTreeInBinary(root->getRightChildHandle(), huffmanTree, treeInBinary);
        }
    }
}

huffman::Encoder::Encoder()
        : headerData_{},
          encodedData_{}
{
}

void
huffman::Encoder::encodeData(const huffman::types::encode_table_t& encode_table, const common::Vector<types::byte_t>& data)
{
    assert(encode_table.size() == constants::CHARACTERS);

    for (auto byte : data)
    {
        types::encode_entry_t encode_entry = encode_table[byte];
        uint32_t code = encode_entry.first;
        uint8_t length = encode_entry.second;
        assert(length != 0);
        encodedData_.push_back(code, length);
    }
}

void huffman::Encoder::createHeader(const huffman::HuffmanTree& huffmanTree)
{
    if (huffmanTree.getRoot() != nullptr)
    {
        writeTreeInBinary(huffmanTree.getRoot()->getHandle(), huffmanTree, headerData_);
    }
}

const common::BitStack& huffman::Encoder::getHeaderData() const
{
    return headerData_;
}


const common::BitStack& huffman::Encoder::getEncodedData() const
{
    return encodedData_;
}



