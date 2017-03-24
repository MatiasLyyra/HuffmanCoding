#include "TreeNode.h"

huffman::TreeNode::TreeNode(types::byte_t data, unsigned frequency, bool isLeaf)
        : data_(data),
          left_(nullptr),
          right_(nullptr),
          frequency_(frequency),
          isLeaf_(isLeaf)
{
}

unsigned char huffman::TreeNode::getData() const
{
    return data_;
}

const huffman::TreeNode* huffman::TreeNode::getLeftChild() const
{
    return left_.get();
}

const huffman::TreeNode* huffman::TreeNode::getRightChild() const
{
    return right_.get();
}

unsigned int huffman::TreeNode::getFrequency() const {
    return frequency_;
}

bool huffman::TreeNode::isLeaf() const {
    return isLeaf_;
}

bool huffman::TreeNode::TreeNodeComparator::operator()(const huffman::TreeNode* a, const huffman::TreeNode* b) const
{
    if (a->frequency_ > b->frequency_)
    {
        return true;
    }
    if (a->frequency_ == b->frequency_)
    {
        if (a->data_ > b->data_)
        {
            return true;
        }
    }
    return false;
}

