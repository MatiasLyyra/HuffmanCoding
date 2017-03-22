#include "HuffmanTree.h"

#include <queue>
#include <ostream>
#include <cassert>
#include <string>

#include "TreeNode.h"


namespace
{
    huffman::types::byte_t readByte(const std::vector<bool>& treeInBinary, uint64_t start)
    {
        huffman::types::byte_t byte = 0;
        for (int i = 0; i < huffman::constants::BITS_IN_BYTE; ++i)
        {
            if (treeInBinary.at(start + i))
            {
                byte |= 1 << (huffman::constants::BITS_IN_BYTE - 1 - i);
            }
        }
        return byte;
    }

    void printTreeRecursive(std::ostream& ostream, const huffman::TreeNode& root, std::string& string)
    {
        if (root.isLeaf())
        {
            ostream << string << " : " << root.getData() << std::endl;
        }
        else
        {
            assert(root.getLeftChild() != nullptr);
            assert(root.getRightChild() != nullptr);

            string += "0";
            printTreeRecursive(ostream, *root.getLeftChild(), string);
            string.pop_back();

            string += "1";
            printTreeRecursive(ostream, *root.getRightChild(), string);
            string.pop_back();

        }
    }

    void collectCharacterCodes(huffman::types::encode_table_t& encode_table, const huffman::TreeNode& root,
                               uint32_t code, uint8_t depth)
    {
        if (root.isLeaf())
        {
            encode_table[root.getData()] = huffman::types::encode_entry_t{code, depth};
        }
        else
        {
            uint32_t leftCode = code << 1;
            uint32_t rightCode = (code << 1) + 1;
            ++depth;

            assert(root.getLeftChild() != nullptr);
            assert(root.getRightChild() != nullptr);
            assert(depth < huffman::constants::MAX_CODE_LENGTH);

            collectCharacterCodes(encode_table, *root.getLeftChild(), leftCode, depth);
            collectCharacterCodes(encode_table, *root.getRightChild(), rightCode, depth);

        }
    }

    std::array<unsigned, huffman::constants::CHARACTERS>
    calculateCharacterFrequencies(const std::vector<huffman::types::byte_t>& characters)
    {
        std::array<unsigned, huffman::constants::CHARACTERS> frequencies{};
        for (auto i : characters)
        {
            ++frequencies[i];
        }
        return frequencies;
    }


}

huffman::HuffmanTree::HuffmanTree(const std::vector<types::byte_t>& characters) : root_(nullptr)
{
    constructTree(characters);
}

huffman::HuffmanTree::HuffmanTree(const std::vector<bool>& treeInBinary) : root_(nullptr)
{
    uint64_t index = 0;
    TreeNode* root = readNodes(treeInBinary, index);
    root_.reset(root);
}

void huffman::HuffmanTree::constructTree(const std::vector<types::byte_t>& characters)
{
    if (characters.empty())
    {
        return;
    }
    std::priority_queue<TreeNode*, std::vector<TreeNode*>, TreeNode::TreeNodeComparator> queue;

    auto frequencies = calculateCharacterFrequencies(characters);
    for (int i = 0; i < constants::CHARACTERS; ++i) {
        if (frequencies[i] != 0)
        {
            TreeNode* leaf = new TreeNode{static_cast<types::byte_t>(i)};
            leaf->isLeaf_ = true;
            leaf->frequency_ = frequencies[i];
            queue.push(leaf);
        }
    }

    while (queue.size() > 1)
    {
        TreeNode* left = queue.top();
        queue.pop();
        TreeNode* right = queue.top();
        queue.pop();

        TreeNode* parent = new TreeNode;
        parent->frequency_ = left->frequency_ + right->frequency_;
        parent->left_.reset(left);
        parent->right_.reset(right);
        queue.push(parent);
    }
    TreeNode* root = queue.top();
    queue.pop();
    root_.reset(root);
}

void huffman::HuffmanTree::printTree(std::ostream& ostream) const
{
    if (root_ == nullptr)
    {
        return;
    }
    std::string buffer;
    printTreeRecursive(ostream, *root_, buffer);
}

const huffman::TreeNode* huffman::HuffmanTree::getRoot() const
{
    return root_.get();
}

huffman::types::encode_table_t huffman::HuffmanTree::constructEncodingTable() const {
    types::encode_table_t encode_table{};
    if (root_ != nullptr)
    {
        collectCharacterCodes(encode_table, *root_, 0, 0);
    }
    return encode_table;
}

huffman::HuffmanTree::~HuffmanTree()
{

}

huffman::TreeNode* huffman::HuffmanTree::readNodes(const std::vector<bool>& treeInBinary, uint64_t& index)
{
    if (treeInBinary.at(index++))
    {
        huffman::types::byte_t byte = readByte(treeInBinary, index);
        index += huffman::constants::BITS_IN_BYTE;
        TreeNode* leaf = new huffman::TreeNode{byte};
        leaf->isLeaf_ = true;
        return leaf;
    }
    TreeNode* parent = new TreeNode;
    TreeNode* left = readNodes(treeInBinary, index);
    TreeNode* right = readNodes(treeInBinary, index);
    parent->left_.reset(left);
    parent->right_.reset(right);
    return parent;
}


