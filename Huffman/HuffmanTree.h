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
        HuffmanTree();
        HuffmanTree(const HuffmanTree& treeNode) = delete;
        HuffmanTree& operator=(const HuffmanTree&) = delete;
        void constructTree(const std::vector<types::byte_t>& characters);
        types::encode_table_t constructEncodingTable() const;
        void printTree(std::ostream& ostream) const;
        const TreeNode* getRoot() const;

    private:
        std::unique_ptr<TreeNode> root_;
    };

}

#endif //HUFFMANCODING_HUFFMANTREE_H
