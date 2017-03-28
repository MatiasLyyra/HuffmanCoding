#include "TreeNode.h"

huffman::TreeNode::TreeNode(handle_t handle, types::byte_t data, unsigned frequency, bool isLeaf)
        : handle_(handle),
          data_(data),
          left_(empty_handle),
          right_(empty_handle),
          frequency_(frequency),
          isLeaf_(isLeaf)
{
}

unsigned char huffman::TreeNode::getData() const
{
    return data_;
}

huffman::TreeNode::handle_t huffman::TreeNode::getLeftChildHandle() const
{
    return left_;
}

huffman::TreeNode::handle_t huffman::TreeNode::getRightChildHandle() const
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

huffman::TreeNode::handle_t huffman::TreeNode::getHandle() const
{
    return handle_;
}


