#include "gtest/gtest.h"

#include "huffman/io/FileUtils.h"
#include "huffman/Decoder.h"
#include "TestUtils.h"

class DecoderFixture :
        public ::testing::Test
{
public:
    huffman::Decoder decoder;
};

// Encoding table: a: 0 d: 101 e: 110 c: 111 B: 1000 b: 1001
TEST_F(DecoderFixture, DecodingWorks)
{
    common::BitStack encodedData;
    huffman::types::byte_t expectedBytes[10] = {'d', 'd', 'c', 'B', 'a', 'a', 'e', 'b', 'd', 'B'};
    std::string encodedString = "10110111110000011010011011000";
    for (int i = 0; i < encodedString.size(); ++i)
    {
        encodedData.push_back(encodedString[i] == '1');
    }
    decoder.decodeData(testutils::getExpectedHuffmanTreeInBinary(), encodedData);
    const common::Vector<huffman::types::byte_t>& actualBytes = decoder.getDecodedData();
    ASSERT_EQ(10, actualBytes.size());
    for (int i = 0; i < 10; ++i)
    {
        ASSERT_EQ(expectedBytes[i], actualBytes[i]);
    }
}

TEST_F(DecoderFixture, DecoderDoesNotThrowWithGarbageValues)
{
    std::string encodedString = "010101011110011101010101010101111100000101010111010";
    common::BitStack encodedData;
    for (int i = 0; i < encodedString.size(); ++i)
    {
        encodedData.push_back(encodedString[i] == '1');
    }
    ASSERT_NO_THROW(decoder.decodeData(testutils::getExpectedHuffmanTreeInBinary(), encodedData));
}
