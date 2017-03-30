#include "TreeNode.h"

huffman::TreeNode::TreeNode(types::handle_t handle, types::byte_t data, unsigned frequency, bool isLeaf)
        : handle_(handle),
          data_(data),
          left_(constants::empty_handle),
          right_(constants::empty_handle),
          frequency_(frequency),
          isLeaf_(isLeaf)
{
}

unsigned char huffman::TreeNode::getData() const
{
    return data_;
}

huffman::types::handle_t huffman::TreeNode::getLeftChildHandle() const
{
    return left_;
}

huffman::types::handle_t huffman::TreeNode::getRightChildHandle() const
{
    return right_;
}

unsigned int huffman::TreeNode::getFrequency() const
{
    return frequency_;
}

bool huffman::TreeNode::isLeaf() const
{
    return isLeaf_;
}

huffman::types::handle_t huffman::TreeNode::getHandle() const
{
    return handle_;
}


