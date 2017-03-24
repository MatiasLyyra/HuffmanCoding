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

    class HuffmanTree {

    public:
        explicit HuffmanTree(const std::vector<types::byte_t>& characters);
        explicit HuffmanTree(const std::vector<bool>& treeInBinary);
        HuffmanTree(const HuffmanTree& treeNode) = delete;
        HuffmanTree& operator=(const HuffmanTree&) = delete;
        HuffmanTree(HuffmanTree&& huffmanTree);
        HuffmanTree& operator=(HuffmanTree&& other);
        ~HuffmanTree();
        types::encode_table_t constructEncodingTable() const;
        void printTree(std::ostream& ostream) const;
        const TreeNode* getRoot() const;

    private:
        void constructTree(const std::vector<types::byte_t>& characters);
        huffman::TreeNode* readNodes(const std::vector<bool>& treeInBinary, uint64_t& index);
        std::unique_ptr<TreeNode> root_;
    };

}

#endif //HUFFMANCODING_HUFFMANTREE_H
