#include "gtest/gtest.h"
#include "huffman/TreeNode.h"

class TreeNodeFixture : public ::testing::Test
{
public:
    TreeNodeFixture()
            : defaultNode(),
              aNode('a', 50, true),
              ANode('A', 50, true),
              bNode('b', 25, true),
              parentNode('\0', 10)
    {
    }


    huffman::TreeNode defaultNode;
    huffman::TreeNode aNode;
    huffman::TreeNode ANode;
    huffman::TreeNode bNode;
    huffman::TreeNode parentNode;

};

TEST_F(TreeNodeFixture, NodesAreConstructedCorrectly)
{
    ASSERT_EQ('\0', defaultNode.getData());
    ASSERT_EQ('a', aNode.getData());
    ASSERT_EQ('A', ANode.getData());
    ASSERT_EQ('b', bNode.getData());
    ASSERT_EQ('\0', parentNode.getData());

    ASSERT_FALSE(defaultNode.isLeaf());
    ASSERT_TRUE(aNode.isLeaf());
    ASSERT_FALSE(parentNode.isLeaf());

    ASSERT_EQ(0, defaultNode.getFrequency());
    ASSERT_EQ(50, aNode.getFrequency());
    ASSERT_EQ(50, ANode.getFrequency());
    ASSERT_EQ(25, bNode.getFrequency());
    ASSERT_EQ(10, parentNode.getFrequency());
}

TEST_F(TreeNodeFixture, ComparingNodesWorks)
{
    huffman::TreeNode::TreeNodeComparator comparator;
    ASSERT_TRUE(comparator(&aNode, &ANode));
    ASSERT_FALSE(comparator(&aNode, &aNode));
    ASSERT_FALSE(comparator(&ANode, &aNode));
    ASSERT_TRUE(comparator(&aNode, &bNode));
    ASSERT_FALSE(comparator(&bNode, &aNode));
    ASSERT_TRUE(comparator(&parentNode, &defaultNode));
    ASSERT_FALSE(comparator(&defaultNode, &parentNode));
}