//
// Created by Matias-PC on 15.3.2017.
//

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
        void constructTree(const std::vector<unsigned char>& characters);
        types::encode_table_t constructEncodingTable() const;
        void printTree(std::ostream& ostream) const;
        const TreeNode* getRoot() const;

    private:
        std::unique_ptr<TreeNode> root_;
    };

}


#endif //HUFFMANCODING_HUFFMANTREE_H
