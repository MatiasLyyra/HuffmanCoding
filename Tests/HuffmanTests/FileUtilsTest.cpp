#include <gtest/gtest.h>
#include <sstream>

#include "huffman/io/FileUtils.h"
#include "TestUtils.h"


class FileUtilsFixture : public ::testing::Test
{
public:
    std::vector<bool> binaryData;
    std::vector<bool>::size_type expextedLength;
protected:
    virtual void SetUp() {
        binaryData = testutils::getExpectedHuffmanTreeInBinary();
        expextedLength = binaryData.size();
    }
};

TEST(FileUtils, ReadFileWorks)
{
    std::string message = "Hello, World!";
    std::istringstream iss{message};
    std::vector<huffman::types::byte_t> characters{huffman::io::readFile(iss)};
    huffman::types::byte_t expected[13] = {'H', 'e', 'l', 'l', 'o', ',', ' ', 'W', 'o', 'r', 'l', 'd','!'};
    ASSERT_EQ(13, characters.size());
    for (int i = 0; i < 13; ++i)
    {
        ASSERT_EQ(expected[i], characters[i]);
    }
}

TEST_F(FileUtilsFixture, WriteBinaryFileWorks)
{
    std::stringstream ss;
    huffman::io::writeBinaryFile(ss, binaryData);
    // Add padding to the end of the binary data so it would match the stream
    while (binaryData.size() % huffman::constants::BITS_IN_BYTE != 0)
    {
        binaryData.push_back(false);
    }
    uint8_t data[8];
    ss.read(reinterpret_cast<char*>(data), sizeof(data));
    uint64_t length = huffman::io::read64BitNumber(data);
    ASSERT_EQ(expextedLength, length);
    std::vector<bool>::size_type i = 0;
    while (!ss.eof())
    {
        uint8_t expected = 0;
        for (int j = (huffman::constants::BITS_IN_BYTE - 1); j >= 0 && i < binaryData.size() ; --j, ++i)
        {
            if (binaryData.at(i))
                expected |= 1 << j;
        }
        uint8_t actual = 0;
        ss.read(reinterpret_cast<char*>(&actual), sizeof(uint8_t));
        ASSERT_EQ(expected, actual);
    }
}

TEST_F(FileUtilsFixture, ReadingBinaryFileWorks)
{
    std::stringstream ss;
    huffman::io::writeBinaryFile(ss, binaryData);
    std::vector<bool> actualData = huffman::io::readBinaryFile(ss, false);
    ASSERT_EQ(actualData.size(), binaryData.size());
    for (int i = 0; i < binaryData.size(); ++i)
    {
        ASSERT_EQ(binaryData[i], actualData[i]);
    }
}

TEST(FileUtils, WritingFileWorks)
{
    std::string message = "Hello, World!";
    std::vector<huffman::types::byte_t> characters{testutils::convertStringToByteVector(message)};
    auto expectedSize = characters.size();
    std::stringstream ss;
    huffman::io::writeFile(ss, characters);
    ss.seekg(0, std::ios::end);
    auto size = ss.tellg();
    ss.seekg(0, std::ios::beg);
    ASSERT_EQ(expectedSize, size);

    for (int i = 0; i < expectedSize; ++i)
    {
        huffman::types::byte_t actual;
        ss.read(reinterpret_cast<char*>(&actual), sizeof(huffman::types::byte_t));
        ASSERT_EQ(characters[i], actual);
    }
}
