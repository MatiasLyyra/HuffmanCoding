#include "FileUtils.h"

#include <fstream>
#include <cassert>

#define DATA_SIZE(size_in_bits) (size_in_bits + (32 - (size_in_bits % 32))) / 8

uint64_t huffman::io::readUint64(std::istream& istream)
{
    uint8_t data[8];
    istream.read(reinterpret_cast<char*>(data), sizeof(data));
    uint64_t number = 0;
    for (int i = 0; i < 8; ++i)
    {
        number |= static_cast<uint64_t>(data[i]) << (i * huffman::constants::BITS_IN_BYTE);
    }
    return number;
}

void huffman::io::writeUint64(uint64_t number, std::ostream& ostream)
{
    uint8_t data[8];

    for (int i = 0; i < 8; ++i)
    {
        data[i] = static_cast<uint8_t>(number >> (i * constants::BITS_IN_BYTE));
    }
    ostream.write(reinterpret_cast<char*>(data), sizeof(data));
}

common::Vector<huffman::types::byte_t> huffman::io::readFile(std::istream& istream)
{
    std::streampos fileSize;
    istream.seekg(0, std::ios::end);
    fileSize = istream.tellg();
    istream.seekg(0, std::ios::beg);

    std::unique_ptr<types::byte_t[]> buffer{new unsigned char[fileSize]};
    istream.read(reinterpret_cast<char*>(buffer.get()), fileSize * sizeof(types::byte_t));
    return common::Vector<types::byte_t>{buffer.get(), buffer.get() + fileSize * sizeof(types::byte_t)};
}

void huffman::io::writeBinaryFile(std::ostream& ostream, const common::BitStack& data, bool magicNumber)
{
    if (magicNumber)
    {
        writeMagicNumber(ostream);
    }
    uint64_t length = data.size();
    writeUint64(length, ostream);
    auto it = data.data();
    auto containerSize = data.container_size();
    types::byte_t bytes[4];
    for (std::size_t i = 0; i < containerSize; ++i)
    {
        uint32_t word = it[i];
        bytes[0] = static_cast<types::byte_t>(word >> 24);
        bytes[1] = static_cast<types::byte_t>(word >> 16);
        bytes[2] = static_cast<types::byte_t>(word >> 8);
        bytes[3] = static_cast<types::byte_t>(word);
        ostream.write(reinterpret_cast<char*>(bytes), sizeof(types::byte_t) * 4);
    }
}

common::BitStack huffman::io::readBinaryFile(std::istream& istream, bool ignoreHeader)
{
    bool validMagicNumber = verifyMagicNumber(istream);
    if (!validMagicNumber)
    {
        throw std::invalid_argument("Invalid file. Magic number does not match.");
    }
    uint8_t data[8];
    uint64_t length = readUint64(istream);
    common::BitStack encodedData;
    uint64_t dataSize = DATA_SIZE(length);
    if (ignoreHeader)
    {
        istream.seekg(dataSize, std::ios::cur);
        length = readUint64(istream);
        dataSize = DATA_SIZE(length);
    }
    encodedData.reserve(length);

    for (auto i = 0; i < dataSize; ++i)
    {
        uint8_t byte;
        istream.read(reinterpret_cast<char*>(&byte), sizeof(uint8_t));
        encodedData.push_back(byte, constants::BITS_IN_BYTE);
    }
    while (encodedData.size() > length)
    {
        encodedData.pop_back();
    }
    return encodedData;
}

void huffman::io::writeFile(std::ostream& ostream, const common::Vector<huffman::types::byte_t>& data)
{
    ostream.write(reinterpret_cast<const char*>(data.begin()), data.size() * sizeof(types::byte_t));
}

void huffman::io::insertByte(huffman::types::byte_t byte, common::BitStack& vector)
{
    for (int i = 0; i < huffman::constants::BITS_IN_BYTE; ++i)
    {
        huffman::types::byte_t mask = static_cast<huffman::types::byte_t>(1
                << huffman::constants::BITS_IN_BYTE - 1 - i);
        vector.push_back((byte & mask) != 0);
    }
}

huffman::types::byte_t huffman::io::readByte(const common::BitStack& vector, uint64_t start)
{
    assert(start > 0 && start <= (vector.size() - huffman::constants::BITS_IN_BYTE));
    huffman::types::byte_t byte = 0;
    for (int i = 0; i < huffman::constants::BITS_IN_BYTE; ++i)
    {
        if (vector.at(start + i))
        {
            byte |= 1 << (huffman::constants::BITS_IN_BYTE - 1 - i);
        }
    }
    return byte;
}

bool huffman::io::verifyMagicNumber(std::istream& istream)
{
    uint64_t magicNumber = readUint64(istream);
    return magicNumber == constants::MAGIG_NUMBER;
}

void huffman::io::writeMagicNumber(std::ostream& ostream)
{
    writeUint64(constants::MAGIG_NUMBER, ostream);
}
