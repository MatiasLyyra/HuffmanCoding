#include "Decoder.h"

#include "TreeNode.h"
#include "io/FileUtils.h"

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

std::vector<huffman::types::byte_t> huffman::Decoder::decode(const huffman::TreeNode &root)
{
    std::vector<bool> encodedData = io::readBinaryFile(filename_.c_str());
    std::vector<types::byte_t> decodedData;
    const huffman::TreeNode* current;
    for (uint64_t i = 0; i < encodedData.size();)
    {
        current = &root;
        while (!current->isLeaf())
        {
            current = encodedData.at(i) ? current->getRightChild() : current->getLeftChild();
            ++i;
        }
        decodedData.push_back(current->getData());
    }
    return decodedData;
}
