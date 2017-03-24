#ifndef HUFFMANCODING_HUFFMANTREE_H
#define HUFFMANCODING_HUFFMANTREE_H

#include <memory>
#include <iosfwd>
#include <cstdint>
#include <vector>

#include "Common.h"

namespace huffman
{
    class TreeNode;

    /**
     * Class responsible for constructing and holding huffman tree.
     */
    class HuffmanTree
    {

    public:
        /**
         * Constructs huffman tree based on character frequencies in characters vector.
         * @param characters Character vector that is used to calculate character frequencies from.
         */
        explicit HuffmanTree(const std::vector<types::byte_t>& characters);

        /**
         * Constructs huffman tree from binary representation. Constructor expects the vector to contain 1/True for
         * each leaf node followed by byte that contains the character of the node and 0/False for each parent/root node.
         * Binary data has to be in pre-order for this to work correctly.
         * @param treeInBinary Huffman tree in binary representation.
         */
        explicit HuffmanTree(const std::vector<bool>& treeInBinary);

        HuffmanTree(const HuffmanTree& treeNode) = delete;

        HuffmanTree& operator=(const HuffmanTree&) = delete;

        HuffmanTree(HuffmanTree&& huffmanTree);

        HuffmanTree& operator=(HuffmanTree&& other);

        ~HuffmanTree();

        /**
         * Constructs encoding table based on the current Huffman tree.
         * @return Encoding table
         */
        types::encode_table_t constructEncodingTable() const;

        /**
         * Prints characters' encoded representation to the specified stream.
         * @param ostream Stream to print to.
         */
        void printTree(std::ostream& ostream) const;

        /**
         * Returns root of the tree or null if there is not one.
         * @return Root of the tree.
         */
        const TreeNode* getRoot() const;

    private:
        void constructTree(const std::vector<types::byte_t>& characters);

        huffman::TreeNode* readNodes(const std::vector<bool>& treeInBinary, uint64_t& index);

        std::unique_ptr<TreeNode> root_;
    };

}

#endif //HUFFMANCODING_HUFFMANTREE_H
