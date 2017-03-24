#include <vector>
#include <string>

#include "gtest/gtest.h"
#include "TestUtils.h"
#include "huffman/io/FileUtils.h"
#include "huffman/HuffmanTree.h"
#include "huffman/TreeNode.h"
#include "huffman/Common.h"

// Forward declare helper functions
void validateEncodingTable(const huffman::types::encode_table_t& encode_table);
void validateTree(const huffman::TreeNode& root, bool ignoreFrequencies);

// Constructs HuffmanTree with character frequencies of:
// a: 5 c: 3 d: 2 b: 1 B: 1 e: 2
class HuffmanTreeCharactersFixture : public ::testing::Test
{

public:
    HuffmanTreeCharactersFixture() : huffmanTree{std::vector<huffman::types::byte_t>{}}
    {
    }

    virtual void TearDown()
    {
    }

    virtual void SetUp()
    {
        huffmanTree = testutils::createHuffmanTreeFromCharacters();
    }
    huffman::HuffmanTree huffmanTree;
};

// Constructs same tree as the HuffmanTreeCharactersFixture but from binary data read from vector
// Binary data is read in preorder where 1/True means leaf node followed by byte that contains the data
// Parent/Root nodes represent 0/False
/* Expected tree
    +--+
    |14|
    +--+
+--+   |
|a5|   +---+
+--+    |9 |
        ++-+
         | |
     +--++ +-----+
     |4 |     |5 |
     +--+     +--+
   +------+ +------+
   |2 ||d2| |e2||c3|
 +---+----+ +------+
 |   |
++---+-+
|B1||b1|
+------+
 */
class HuffmanTreeBinaryFixture : public ::testing::Test
{

public:
    HuffmanTreeBinaryFixture() : huffmanTreeBinary{std::vector<bool>{}}
    {
    }
    virtual void TearDown()
    {

    }

    virtual void SetUp()
    {
        huffmanTreeBinary = testutils::createHuffmanTreeFromBinary();
    }
    huffman::HuffmanTree huffmanTreeBinary;
};

TEST_F(HuffmanTreeCharactersFixture, TreeIsConstructedCorrectly)
{
    validateTree(*huffmanTree.getRoot(), false);
}
// Encoding table should be following:
// a: 0 d: 101 e: 110 c: 111 B: 1000 b: 1001
TEST_F(HuffmanTreeCharactersFixture, EncodingTableIsCorrect)
{
    validateEncodingTable(huffmanTree.constructEncodingTable());
}

TEST_F(HuffmanTreeBinaryFixture, TreeIsConstructedCorrectlyBinary)
{
    // Ignore frequencies as the HuffmanTree constructed from binary data doesn't contain them
    validateTree(*huffmanTreeBinary.getRoot(), true);
}

TEST_F(HuffmanTreeBinaryFixture, EncodingTableIsCorrectBinary)
{
    validateEncodingTable(huffmanTreeBinary.constructEncodingTable());
}
void validateTree(const huffman::TreeNode& root, bool ignoreFrequencies)
{
    ASSERT_EQ('\0', root.getData());

    ASSERT_EQ('a', root.getLeftChild()->getData());

    const huffman::TreeNode* node9 = root.getRightChild();
    ASSERT_EQ('\0', node9->getData());

    const huffman::TreeNode* node4 = node9->getLeftChild();
    const huffman::TreeNode* node5 = node9->getRightChild();
    ASSERT_EQ('\0', node4->getData());
    ASSERT_EQ('\0', node5->getData());

    ASSERT_EQ('e', node5->getLeftChild()->getData());

    ASSERT_EQ('c', node5->getRightChild()->getData());

    ASSERT_EQ('d', node4->getRightChild()->getData());

    const huffman::TreeNode* node2 = node4->getLeftChild();
    ASSERT_EQ('B', node2->getLeftChild()->getData());
    ASSERT_EQ('b', node2->getRightChild()->getData());

    if (!ignoreFrequencies) {
        ASSERT_EQ(14, root.getFrequency());
        ASSERT_EQ(5, root.getLeftChild()->getFrequency());
        ASSERT_EQ(9, node9->getFrequency());
        ASSERT_EQ(4, node4->getFrequency());
        ASSERT_EQ(5, node5->getFrequency());
        ASSERT_EQ(2, node5->getLeftChild()->getFrequency());
        ASSERT_EQ(3, node5->getRightChild()->getFrequency());
        ASSERT_EQ(2, node4->getRightChild()->getFrequency());
        ASSERT_EQ(1, node2->getLeftChild()->getFrequency());
        ASSERT_EQ(1, node2->getRightChild()->getFrequency());
    }
}
void validateEncodingTable(const huffman::types::encode_table_t& encode_table)
{
    ASSERT_EQ(static_cast<uint32_t>(0), encode_table['a'].first);
    ASSERT_EQ(static_cast<uint8_t>(1), encode_table['a'].second);

    // 101 = 5
    ASSERT_EQ(static_cast<uint32_t>(5), encode_table['d'].first);
    ASSERT_EQ(static_cast<uint8_t>(3), encode_table['d'].second);

    // 110 = 6
    ASSERT_EQ(static_cast<uint32_t>(6), encode_table['e'].first);
    ASSERT_EQ(static_cast<uint8_t>(3), encode_table['e'].second);

    // 111 = 7
    ASSERT_EQ(static_cast<uint32_t>(7), encode_table['c'].first);
    ASSERT_EQ(static_cast<uint8_t>(3), encode_table['c'].second);

    // 1000 = 8
    ASSERT_EQ(static_cast<uint32_t>(8), encode_table['B'].first);
    ASSERT_EQ(static_cast<uint8_t>(4), encode_table['B'].second);

    // 1001 = 9
    ASSERT_EQ(static_cast<uint32_t>(9), encode_table['b'].first);
    ASSERT_EQ(static_cast<uint8_t>(4), encode_table['b'].second);
}