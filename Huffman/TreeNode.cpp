//
// Created by Matias-PC on 15.3.2017.
//

#include "TreeNode.h"

huffman::TreeNode::TreeNode(unsigned char data)
        : data_(data),
          left_(nullptr),
          right_(nullptr),
          frequency_(0),
          isLeaf_(false)
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
    if (a->frequency_ != b->frequency_)
    {
        return a->frequency_ > b->frequency_;
    }
    return a->data_ < b->data_;
}

