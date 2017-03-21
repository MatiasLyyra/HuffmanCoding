//
// Created by Matias-PC on 15.3.2017.
//

#include "gtest/gtest.h"
#include "huffman/HuffmanTree.h"

class HuffmanTreeTest : public ::testing::Test
{

public:
    virtual void TearDown() {
    }

    virtual void SetUp() {

    }
    huffman::HuffmanTree tree;
};

TEST_F(HuffmanTreeTest, Test1)
{
    ASSERT_TRUE(tree.getRoot() == nullptr);
}