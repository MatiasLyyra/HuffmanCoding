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

        using handle_t = int;
        static constexpr int empty_handle = -1;
        /**
         * Constructs node based on given arguments.
         * @param handle Handle to this node.
         * @param data Data that the node holds. Default is 0.
         * @param frequency Frequency of the data. Default is 0.
         * @param isLeaf Whether Node is leaf. Default is false.
         */
        explicit TreeNode(handle_t handle, types::byte_t data = 0, unsigned frequency = 0, bool isLeaf = false);

        types::byte_t getData() const;

        handle_t getHandle() const;

        handle_t getLeftChildHandle() const;

        handle_t getRightChildHandle() const;

        unsigned getFrequency() const;

        bool isLeaf() const;

    private:
        handle_t handle_;
        types::byte_t data_;
        handle_t left_;
        handle_t right_;
        unsigned frequency_;
        bool isLeaf_;
    };

}


#endif //HUFFMANCODING_TREENODE_H
