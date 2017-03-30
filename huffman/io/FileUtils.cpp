#include "FileUtils.h"

#include <fstream>
#include <memory>
#include <cassert>
#include <Vector.h>


uint64_t huffman::io::read64BitNumber(const uint8_t (&data)[8])
{
    uint64_t number = 0;
    for (int i = 0; i < 8; ++i)
    {
        number |= data[i] << (i * huffman::constants::BITS_IN_BYTE);
    }
    return number;
}

void huffman::io::write64BitNumberToStream(uint64_t number, std::ostream& ostream)
{
    uint8_t data[8];

    for (int i = 0; i < 8; ++i)
    {
        data[i] = static_cast<uint8_t>((number & (0xff << (i * huffman::constants::BITS_IN_BYTE)))
                >> i * huffman::constants::BITS_IN_BYTE);
    }
    ostream.write(reinterpret_cast<char*>(&data[0]), sizeof(data));
}

common::Vector<huffman::types::byte_t> huffman::io::readFile(std::istream& istream)
{
    std::streampos fileSize;
    istream.seekg(0, std::ios::end);
    fileSize = istream.tellg();
    istream.seekg(0, std::ios::beg);

    std::unique_ptr<types::byte_t[]> buffer{new unsigned char[fileSize]};
    istream.read(reinterpret_cast<char*>(&buffer.get()[0]), fileSize * sizeof(types::byte_t));
    return common::Vector<types::byte_t>{buffer.get(), buffer.get() + fileSize * sizeof(types::byte_t)};
}

void huffman::io::writeBinaryFile(std::ostream& ostream, const std::vector<bool>& data)
{
    uint64_t length = data.size();
    write64BitNumberToStream(length, ostream);
    for (uint64_t i = 0; i < length;)
    {
        huffman::types::byte_t byte = 0;
        for (uint8_t j = 0; j < constants::BITS_IN_BYTE && i < length; ++j, ++i)
        {
            if (data.at(i))
            {
                byte |= 1 << (constants::BITS_IN_BYTE - 1 - j);
            }
        }
        ostream.write(reinterpret_cast<char*>(&byte), sizeof(types::byte_t));
    }
}

std::vector<bool> huffman::io::readBinaryFile(std::istream& istream, bool ignoreHeader)
{
    uint8_t data[8];
    istream.read(reinterpret_cast<char*>(&data[0]), sizeof(data));
    uint64_t length = read64BitNumber(data);
    if (ignoreHeader)
    {
        //Round length up to closest multiple of 8
        uint64_t dataSize = (length + huffman::constants::BITS_IN_BYTE - 1 -
                             (length + huffman::constants::BITS_IN_BYTE - 1) % huffman::constants::BITS_IN_BYTE) /
                            huffman::constants::BITS_IN_BYTE;
        istream.seekg(dataSize, std::ios::cur);
        istream.read(reinterpret_cast<char*>(&data[0]), sizeof(data));
        length = read64BitNumber(data);
    }
    std::vector<bool> encodedData;
    encodedData.resize(length);

    for (uint64_t i = 0; i < length;)
    {
        uint8_t byte;
        istream.read(reinterpret_cast<char*>(&byte), sizeof(uint8_t));
        for (int j = 0; j < constants::BITS_IN_BYTE && i < length; ++j, ++i)
        {
            bool value = (byte & (1 << (constants::BITS_IN_BYTE - 1 - j))) != 0;
            encodedData[i] = value;
        }
    }
    return encodedData;
}

void huffman::io::writeFile(std::ostream& ostream, const common::Vector<huffman::types::byte_t>& data)
{
    ostream.write(reinterpret_cast<const char*>(data.begin()), data.size() * sizeof(types::byte_t));
}

void huffman::io::insertByte(huffman::types::byte_t byte, std::vector<bool>& vector)
{
    for (int i = 0; i < huffman::constants::BITS_IN_BYTE; ++i)
    {
        huffman::types::byte_t mask = static_cast<huffman::types::byte_t>(1
                << huffman::constants::BITS_IN_BYTE - 1 - i);
        vector.push_back((byte & mask) != 0);
    }
}

huffman::types::byte_t huffman::io::readByte(const std::vector<bool>& vector, uint64_t start)
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
