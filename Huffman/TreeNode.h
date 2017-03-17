//
// Created by Matias-PC on 15.3.2017.
//

#ifndef HUFFMANCODING_TREENODE_H
#define HUFFMANCODING_TREENODE_H

#include <memory>

namespace huffman
{
    class TreeNode {

    friend class HuffmanTree;

    public:
        struct TreeNodeComparator
        {
            bool operator()(const TreeNode* a, const TreeNode* b) const;
        };

        explicit TreeNode(unsigned char data = '\0');
        TreeNode(const TreeNode& treeNode) = delete;
        TreeNode& operator=(const TreeNode&) = delete;
        unsigned char getData() const;
        const TreeNode* getLeftChild() const;
        const TreeNode* getRightChild() const;
        unsigned getFrequency() const;
        bool isLeaf() const;
    private:
        unsigned char data_;
        std::unique_ptr<TreeNode> left_;
        std::unique_ptr<TreeNode> right_;
        unsigned frequency_;
        bool isLeaf_;
    };

}



#endif //HUFFMANCODING_TREENODE_H
