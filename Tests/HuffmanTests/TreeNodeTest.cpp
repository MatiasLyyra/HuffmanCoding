#include "gtest/gtest.h"
#include "huffman/TreeNode.h"

class TreeNodeFixture : public ::testing::Test
{
public:
    TreeNodeFixture()
            : defaultNode(0),
              aNode(1, 'a', 50, true),
              ANode(2, 'A', 50, true),
              bNode(3, 'b', 25, true),
              parentNode(4, '\0', 10)
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
