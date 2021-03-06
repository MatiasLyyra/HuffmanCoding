#include <gtest/gtest.h>
#include <sstream>

#include "huffman/io/FileUtils.h"
#include "huffman/HuffmanTree.h"
#include "huffman/Encoder.h"
#include "TestUtils.h"


class FileUtilsFixture :
        public ::testing::Test
{
public:
    common::BitStack binaryData;
    common::BitStack::size_type expectedLength;
protected:
    virtual void SetUp()
    {
        binaryData = testutils::getExpectedHuffmanTreeInBinary();
        expectedLength = binaryData.size();
    }
};

TEST(FileUtils, ReadFileWorks)
{
    std::string message = "Hello, World!";
    std::istringstream iss{message};
    common::Vector<huffman::types::byte_t> characters{huffman::io::readFile(iss)};
    huffman::types::byte_t expected[13] = {'H', 'e', 'l', 'l', 'o', ',', ' ', 'W', 'o', 'r', 'l', 'd', '!'};
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
    uint64_t length = huffman::io::readUint64(ss);
    ASSERT_EQ(expectedLength, length);
    std::vector<bool>::size_type i = 0;
    while (!ss.eof())
    {
        uint8_t expected = 0;
        for (int j = (huffman::constants::BITS_IN_BYTE - 1); j >= 0 && i < binaryData.size(); --j, ++i)
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
    huffman::io::writeBinaryFile(ss, binaryData, true);
    common::BitStack actualData = huffman::io::readBinaryFile(ss, false);
    ASSERT_EQ(actualData.size(), binaryData.size());
    for (int i = 0; i < binaryData.size(); ++i)
    {
        ASSERT_EQ(binaryData[i], actualData[i]);
    }
}

TEST(FileUtils, WritingFileWorks)
{
    std::string message = "Hello, World!";
    common::Vector<huffman::types::byte_t> characters{testutils::convertStringToByteVector(message)};
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

TEST(FileUtils, MagicNumberIsWrittenToStream)
{
    std::stringstream ss;
    common::BitStack bitStack;
    huffman::io::writeBinaryFile(ss, bitStack, true);
    ss.seekg(0, std::ios::beg);
    uint64_t magicNumber = huffman::io::readUint64(ss);
    ASSERT_EQ(huffman::constants::MAGIG_NUMBER, magicNumber);
}

TEST(FileUtils, InvalidMagicNumberCausesError)
{
    std::stringstream ss;
    ss << "aaaaaaaaaaaaaaaaaaaaaaa";
    ss.seekg(0, std::ios::beg);
    ASSERT_THROW(huffman::io::readBinaryFile(ss, true), std::invalid_argument);
}

TEST(FileUtils, CorrectMagicNumberDoesNotCauseError)
{
    std::stringstream ss;
    huffman::io::writeUint64(huffman::constants::MAGIG_NUMBER, ss);
    ss.seekg(0, std::ios::beg);
    ASSERT_NO_THROW(huffman::io::readBinaryFile(ss, true));
}

TEST(FileUtils, IgnoreHeaderWorks)
{
    auto vector = testutils::convertStringToByteVector("Hello, World!");
    huffman::HuffmanTree huffmanTree{vector};
    huffman::Encoder encoder;
    encoder.encodeData(huffmanTree.constructEncodingTable(), vector);
    encoder.createHeader(huffmanTree);

    std::stringstream ss;
    huffman::io::writeBinaryFile(ss, encoder.getHeaderData(), true);
    ss.seekg(0, std::ios::beg);
    huffman::io::writeBinaryFile(ss, encoder.getEncodedData());
    ss.seekg(0, std::ios::beg);

    auto encodedData = huffman::io::readBinaryFile(ss, true);

    ASSERT_EQ(encoder.getEncodedData().size(), encodedData.size());
    for (int i = 0; i < encoder.getEncodedData().size(); ++i)
    {
        ASSERT_EQ(encoder.getEncodedData()[i], encodedData[i]);
    }
}