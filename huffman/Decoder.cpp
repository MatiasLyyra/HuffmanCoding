#include "Decoder.h"

#include "TreeNode.h"
#include "io/FileUtils.h"
#include "HuffmanTree.h"

namespace
{
    huffman::types::byte_t decodeByte(const huffman::TreeNode& root, const std::vector<bool>& data, uint64_t& i)
    {
        if (root.isLeaf())
        {
            i--;
            return root.getData();
        }
        if (data.at(i))
        {
            i++;
            return decodeByte(*root.getRightChild(), data, i);
        }
        i++;
        return decodeByte(*root.getLeftChild(), data, i);
    }
}

huffman::Decoder::Decoder(const std::string &filename) : filename_(filename)
{

}

std::vector<huffman::types::byte_t> huffman::Decoder::decode()
{
    std::vector<bool> treeInBinary = io::readBinaryFile(filename_.c_str(), false);
    std::vector<bool> encodedData = io::readBinaryFile(filename_.c_str(), true);
    std::vector<types::byte_t> decodedData;
    huffman::HuffmanTree huffmanTree{treeInBinary};
    const huffman::TreeNode* current;
    for (uint64_t i = 0; i < encodedData.size();)
    {
        current = huffmanTree.getRoot();
        while (!current->isLeaf())
        {
            current = encodedData.at(i) ? current->getRightChild() : current->getLeftChild();
            ++i;
        }
        decodedData.push_back(current->getData());
    }
    return decodedData;
}
