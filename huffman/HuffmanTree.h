#ifndef HUFFMANCODING_HUFFMANTREE_H
#define HUFFMANCODING_HUFFMANTREE_H

#include <memory>
#include <iosfwd>
#include <cstdint>
#include <vector>

#include "Vector.h"
#include "Common.h"
#include "TreeNode.h"

namespace huffman
{
    /**
     * Class responsible for constructing and holding huffman tree.
     */
    class HuffmanTree
    {

    public:
         /**
         * Comparator used for determining order of the nodes when constructing the tree. Nodes are primarily ordered
         * by frequency where lower frequency has higher priority. Nodes are secondarily ordered by the data where
         * smaller data value has higher priority.
         */
        struct TreeNodeComparator
        {
            TreeNodeComparator(const huffman::HuffmanTree& huffmanTree) : huffmanTree_(huffmanTree)
            {}
            bool operator()(const huffman::types::handle_t &aHandle, const huffman::types::handle_t &bHandle) const;
            const huffman::HuffmanTree& huffmanTree_;
        };
        /**
         * Constructs huffman tree based on character frequencies in characters vector.
         * @param characters Character vector that is used to calculate character frequencies from.
         */
        explicit HuffmanTree(const common::Vector<types::byte_t>& characters);

        /**
         * Constructs huffman tree from binary representation. Constructor expects the vector to contain 1/True for
         * each leaf node followed by byte that contains the character of the node and 0/False for each parent/root node.
         * Binary data has to be in pre-order for this to work correctly.
         * @param treeInBinary Huffman tree in binary representation.
         */
        explicit HuffmanTree(const std::vector<bool>& treeInBinary);

        const TreeNode* getNode(types::handle_t handle) const;

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
        void constructTree(const common::Vector<types::byte_t>& characters);

        types::handle_t getNextFreeHandle();

        void collectCharacterCodes(types::encode_table_t& encode_table, types::handle_t rootHandle,
                                   uint32_t code, uint8_t depth) const;

        void printTreeRecursive(std::ostream& ostream, types::handle_t root, std::string& string) const;

        types::handle_t readNodes(const std::vector<bool>& treeInBinary, uint64_t& index);

        common::Vector<TreeNode> nodes_;
        types::handle_t root_;
    };

}

#endif //HUFFMANCODING_HUFFMANTREE_H
