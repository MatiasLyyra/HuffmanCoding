#include "Decoder.h"

#include "TreeNode.h"
#include "HuffmanTree.h"

huffman::Decoder::Decoder() : decodedData_{}
{

}

void huffman::Decoder::decodeData(const common::BitStack& treeInBinary, const common::BitStack& encodedData)
{
    huffman::HuffmanTree huffmanTree{treeInBinary};
    const huffman::TreeNode* current;
    for (uint64_t i = 0; i < encodedData.size();)
    {
        current = huffmanTree.getRoot();
        while (!current->isLeaf() && i < encodedData.size())
        {
            current = encodedData.at(i) ? huffmanTree.getNode(current->getRightChildHandle()) : huffmanTree.getNode(
                    current->getLeftChildHandle());
            ++i;
        }
        decodedData_.push_back(current->getData());
    }

}

const common::Vector<huffman::types::byte_t>& huffman::Decoder::getDecodedData() const
{
    return decodedData_;
}
