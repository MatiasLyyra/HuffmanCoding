#include <huffman/Encoder.h>
#include <huffman/HuffmanTree.h>
#include "gtest/gtest.h"
#include "TestUtils.h"

class EncoderFixture :
        public ::testing::Test
{

public:

    virtual void TearDown()
    {

    }

    virtual void SetUp()
    {

    }

    huffman::Encoder encoder;
};

// Encoding table: a: 0 d: 101 e: 110 c: 111 B: 1000 b: 1001
TEST_F(EncoderFixture, EncodingWorks)
{
    huffman::HuffmanTree huffmanTree{testutils::createHuffmanTreeFromCharacters()};
    huffman::types::encode_table_t encode_table = huffmanTree.constructEncodingTable();
    std::string message = "aecaaBb";
    common::Vector<huffman::types::byte_t> characters{testutils::convertStringToByteVector(message)};
    std::size_t expectedLength = 17;
    bool expected[expectedLength] = {false, true, true, false, true, true, true, false, false, true, false, false,
                                     false, true,
                                     false, false, true};
    encoder.encodeData(encode_table, characters);
    const common::BitStack& actual = encoder.getEncodedData();
    ASSERT_EQ(expectedLength, actual.size());
    for (std::size_t i = 0; i < expectedLength; ++i)
    {
        ASSERT_EQ(expected[i], actual.at(i));
    }
}

TEST_F(EncoderFixture, HeaderDataIsCorrect)
{
    huffman::HuffmanTree huffmanTree{testutils::createHuffmanTreeFromCharacters()};
    encoder.createHeader(huffmanTree);
    const common::BitStack& actual = encoder.getHeaderData();
    common::BitStack expected{testutils::getExpectedHuffmanTreeInBinary()};
    ASSERT_EQ(expected.size(), actual.size());
    for (std::vector<bool>::size_type i = 0; i < expected.size(); ++i)
    {
        ASSERT_EQ(expected.at(i), expected.at(i));
    }
}