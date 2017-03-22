#include "FileUtils.h"

#include <fstream>
#include <iterator>
#include <memory>

namespace
{
    uint64_t read64BitNumber(const uint8_t (&data)[8])
    {
        uint64_t number = 0;
        for (int i = 0; i < 8; ++i)
        {
            number |= data[i] << (i * huffman::constants::BITS_IN_BYTE);
        }
        return number;
    }

    void write64BitNumber(uint64_t number, std::ofstream& ofstream)
    {
        uint8_t data[8];

        for (int i = 0; i < 8; ++i)
        {
            data[i] = static_cast<uint8_t>((number & (0xff << (i * huffman::constants::BITS_IN_BYTE)))
                     >> i * huffman::constants::BITS_IN_BYTE);
        }
        ofstream.write(reinterpret_cast<char*>(&data[0]), sizeof(data));
    }
}
std::vector<huffman::types::byte_t> huffman::io::readFile(const char* filename)
{
    std::ifstream file{filename, std::ios::binary | std::ios::in};
    if (file.is_open())
    {
        std::streampos fileSize;
        file.seekg(0, std::ios::end);
        fileSize = file.tellg();
        file.seekg(0, std::ios::beg);

        std::unique_ptr<types::byte_t[]> buffer{new unsigned char[fileSize]};
        file.read(reinterpret_cast<char*>(&buffer.get()[0]), fileSize*sizeof(types::byte_t));
        return std::vector<types::byte_t>{buffer.get(), buffer.get() + fileSize*sizeof(types::byte_t)};
    }

    return std::vector<types::byte_t>{};
}

void huffman::io::writeBinaryFile(const char* filename, const std::vector<bool> &data, bool append)
{
    std::ofstream ofstream;
    if (append)
        ofstream.open(filename, std::ios::binary | std::ios::out |  std::ios::app);
    else
        ofstream.open(filename, std::ios::binary | std::ios::out);

    uint64_t length = data.size();
    write64BitNumber(length, ofstream);
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
        ofstream.write(reinterpret_cast<char *>(&byte), sizeof(types::byte_t));
    }
}

std::vector<bool> huffman::io::readBinaryFile(const char* filename, bool ignoreHeader)
{
    uint8_t data[8];
    std::ifstream ifstream{filename, std::ios::in | std::ios::binary};

    ifstream.read(reinterpret_cast<char*>(&data[0]), sizeof(data));
    uint64_t length = read64BitNumber(data);
    if (ignoreHeader)
    {
        //Round length up to closest multiple of 8
        uint64_t dataSize = (length + huffman::constants::BITS_IN_BYTE - 1 -
                            (length + huffman::constants::BITS_IN_BYTE - 1) % huffman::constants::BITS_IN_BYTE) /
                            huffman::constants::BITS_IN_BYTE;
        ifstream.seekg(dataSize, std::ios::cur);
        ifstream.read(reinterpret_cast<char*>(&data[0]), sizeof(data));
        length = read64BitNumber(data);
    }
    std::vector<bool> encodedData;
    encodedData.resize(length);

    for (uint64_t i = 0; i < length;)
    {
        uint8_t byte;
        ifstream.read(reinterpret_cast<char*>(&byte), sizeof(uint8_t));
        for (int j = 0; j < constants::BITS_IN_BYTE && i < length; ++j, ++i)
        {
            bool value = (byte & (1 << (constants::BITS_IN_BYTE - 1 - j))) != 0;
            encodedData[i] = value;
        }
    }
    return encodedData;
}

void huffman::io::writeFile(const char* filename, const std::vector<huffman::types::byte_t>& data)
{
    std::ofstream ofstream{filename, std::ios::binary | std::ios::out};
    ofstream.write(reinterpret_cast<const char*>(data.data()), data.size() * sizeof(types::byte_t));
}
