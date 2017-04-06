#ifndef HUFFMANCODING_TREENODE_H
#define HUFFMANCODING_TREENODE_H

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
         * Constructs node based on given arguments.
         * @param handle Handle to this node.
         * @param data Data that the node holds. Default is 0.
         * @param frequency Frequency of the data. Default is 0.
         * @param isLeaf Whether Node is leaf. Default is false.
         */
        explicit TreeNode(types::handle_t handle, types::byte_t data = 0, unsigned frequency = 0, bool isLeaf = false);

        types::byte_t getData() const;

        types::handle_t getHandle() const;

        types::handle_t getLeftChildHandle() const;

        types::handle_t getRightChildHandle() const;

        unsigned getFrequency() const;

        bool isLeaf() const;

    private:
        types::handle_t handle_;
        types::byte_t data_;
        types::handle_t left_;
        types::handle_t right_;
        unsigned frequency_;
        bool isLeaf_;
    };

}


#endif //HUFFMANCODING_TREENODE_H
