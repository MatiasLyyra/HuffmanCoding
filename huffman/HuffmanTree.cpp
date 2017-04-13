#include "HuffmanTree.h"

#include <ostream>
#include <cassert>

#include "io/FileUtils.h"
#include "common/PriorityQueue.h"

namespace
{
    std::array<unsigned, huffman::constants::CHARACTERS>
    calculateCharacterFrequencies(const common::Vector<huffman::types::byte_t>& characters)
    {
        std::array<unsigned, huffman::constants::CHARACTERS> frequencies{};
        for (auto it = characters.begin(); it != characters.end(); ++it)
        {
            ++frequencies[*it];
        }
        return frequencies;
    }
}

huffman::HuffmanTree::HuffmanTree(const common::Vector<types::byte_t>& characters) : root_(constants::empty_handle), nodes_{}
{
    if (!characters.empty())
    {
        constructTree(characters);
    }
}

huffman::HuffmanTree::HuffmanTree(const common::BitStack& treeInBinary) : root_(constants::empty_handle), nodes_{}
{
    if (!treeInBinary.empty())
    {
        uint64_t index = 0;
        root_ = readNodes(treeInBinary, index);
    }
}

void huffman::HuffmanTree::constructTree(const common::Vector<types::byte_t>& characters)
{
    TreeNodeComparator comparator{*this};
    common::PriorityQueue<types::handle_t, TreeNodeComparator> queue(comparator);

    auto frequencies = calculateCharacterFrequencies(characters);
    for (int i = 0; i < constants::CHARACTERS; ++i)
    {
        if (frequencies[i] != 0)
        {
            TreeNode leaf{getNextFreeHandle(), static_cast<types::byte_t>(i), frequencies[i], true};
            nodes_.push_back(leaf);
            queue.push(leaf.handle_);
        }
    }

    while (queue.size() > 1)
    {
        TreeNode* left = &nodes_[queue.top()];
        queue.pop();
        TreeNode* right = &nodes_[queue.top()];
        queue.pop();

        TreeNode parent{getNextFreeHandle()};
        parent.frequency_ = left->frequency_ + right->frequency_;
        parent.left_ = left->handle_;
        parent.right_ = right->handle_;
        nodes_.push_back(parent);
        queue.push(parent.handle_);
    }
    root_ = queue.top();
    queue.pop();
}

void huffman::HuffmanTree::printTree(std::ostream& ostream) const
{
    if (root_ == constants::empty_handle)
    {
        return;
    }
    std::string buffer;
    printTreeRecursive(ostream, root_, buffer);
}

const huffman::TreeNode* huffman::HuffmanTree::getRoot() const
{
    if (root_ == constants::empty_handle)
    {
        return nullptr;
    }
    return &nodes_[root_];
}

huffman::types::encode_table_t huffman::HuffmanTree::constructEncodingTable() const
{
    types::encode_table_t encode_table{};
    if (root_ != constants::empty_handle)
    {
        collectCharacterCodes(encode_table, root_, 0, 0);
    }
    return encode_table;
}

huffman::HuffmanTree::~HuffmanTree()
{

}

huffman::types::handle_t huffman::HuffmanTree::readNodes(const common::BitStack& treeInBinary, uint64_t& index)
{
    if (treeInBinary.at(index++))
    {
        huffman::types::byte_t byte = huffman::io::readByte(treeInBinary, index);
        index += huffman::constants::BITS_IN_BYTE;
        TreeNode leaf{getNextFreeHandle(), byte, 0, true};
        nodes_.push_back(leaf);
        return leaf.handle_;
    }
    auto left = readNodes(treeInBinary, index);
    auto right = readNodes(treeInBinary, index);

    TreeNode parent{getNextFreeHandle()};
    parent.left_ = left;
    parent.right_ = right;
    nodes_.push_back(parent);
    return parent.handle_;
}


const huffman::TreeNode* huffman::HuffmanTree::getNode(huffman::types::handle_t handle) const
{
    if (handle == constants::empty_handle)
    {
        return nullptr;
    }
    return &nodes_[handle];
}

huffman::types::handle_t huffman::HuffmanTree::getNextFreeHandle()
{
    return static_cast<types::handle_t>(nodes_.size());
}

void huffman::HuffmanTree::collectCharacterCodes(huffman::types::encode_table_t& encode_table,
                                                 huffman::types::handle_t rootHandle,
                                                 uint32_t code, uint8_t depth) const
{
    const huffman::TreeNode* root = getNode(rootHandle);
    if (root->isLeaf())
    {
        encode_table[root->getData()] = huffman::types::encode_entry_t{code, depth};
    }
    else
    {
        uint32_t leftCode = code << 1;
        uint32_t rightCode = (code << 1) + 1;
        ++depth;

        assert(root->getLeftChildHandle() != constants::empty_handle);
        assert(root->getRightChildHandle() != constants::empty_handle);
        assert(depth < huffman::constants::MAX_CODE_LENGTH);

        collectCharacterCodes(encode_table, root->getLeftChildHandle(), leftCode, depth);
        collectCharacterCodes(encode_table, root->getRightChildHandle(), rightCode, depth);

    }
}

void huffman::HuffmanTree::printTreeRecursive(std::ostream& ostream, types::handle_t rootHandle,
                                              std::string& string) const
{
    const TreeNode* root = getNode(rootHandle);
    if (root->isLeaf())
    {
        ostream << string << " : " << root->getData() << std::endl;
    }
    else
    {
        assert(root->getLeftChildHandle() != constants::empty_handle);
        assert(root->getRightChildHandle() != constants::empty_handle);

        string += "0";
        printTreeRecursive(ostream, root->getLeftChildHandle(), string);
        string.pop_back();

        string += "1";
        printTreeRecursive(ostream, root->getRightChildHandle(), string);
        string.pop_back();

    }
}

bool huffman::HuffmanTree::TreeNodeComparator::operator()(const types::handle_t &aHandle, const types::handle_t &bHandle) const
{
    const huffman::TreeNode* a = huffmanTree_.getNode(aHandle);
    const huffman::TreeNode* b = huffmanTree_.getNode(bHandle);
    if (a->getFrequency() > b->getFrequency())
    {
        return true;
    }
    if (a->getFrequency() == b->getFrequency())
    {
        if (a->getData() > b->getData())
        {
            return true;
        }
    }
    return false;
}

