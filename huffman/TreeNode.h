#ifndef HUFFMANCODING_TREENODE_H
#define HUFFMANCODING_TREENODE_H

#include <memory>

#include "Common.h"

namespace huffman
{
    class TreeNode {

    friend class HuffmanTree;

    public:
        struct TreeNodeComparator
        {
            bool operator()(const TreeNode* a, const TreeNode* b) const;
        };

        explicit TreeNode(types::byte_t data = 0, unsigned frequency = 0, bool isLeaf = false);
        TreeNode(const TreeNode& treeNode) = delete;
        TreeNode& operator=(const TreeNode&) = delete;
        types::byte_t getData() const;
        const TreeNode* getLeftChild() const;
        const TreeNode* getRightChild() const;
        unsigned getFrequency() const;
        bool isLeaf() const;
    private:
        types::byte_t data_;
        std::unique_ptr<TreeNode> left_;
        std::unique_ptr<TreeNode> right_;
        unsigned frequency_;
        bool isLeaf_;
    };

}



#endif //HUFFMANCODING_TREENODE_H
