#ifndef HUFFMANCODING_TREENODE_H
#define HUFFMANCODING_TREENODE_H

#include <memory>

#include "Common.h"

namespace huffman
{
    /**
     * Represents single node within Huffman tree.
     */
    class TreeNode
    {

        friend class HuffmanTree;

    public:
        /**
         * Comparator used for determining order of the nodes when constructing the tree. Nodes are primarily ordered
         * by frequency where lower frequency has higher priority. Nodes are secondarily ordered by the data where
         * smaller data value has higher priority.
         */
        struct TreeNodeComparator
        {
            bool operator()(const TreeNode* a, const TreeNode* b) const;
        };

        /**
         * Constructs node based on given arguments.
         * @param data Data that the node holds. Default is 0.
         * @param frequency Frequency of the data. Default is 0.
         * @param isLeaf Whether Node is leaf. Default is false.
         */
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
