#include "Encoder.h"

#include <cassert>
#include <cstdint>
#include <cstring>
#include <fstream>

huffman::Encoder::Encoder(const std::string& fileName)
        : bitsInBuffer_(0),
          fileName_(fileName)
{
    std::memset(&buffer_, 0, sizeof(buffer_));
}

void huffman::Encoder::encodeData(const huffman::types::encode_table_t &encode_table, const std::vector<types::byte_t>& data)
{
    assert(encode_table.size() == constants::CHARACTERS);
    //TODO: Add code that writes the header here
    for (auto byte : data)
    {
        types::encode_entry_t encode_entry = encode_table[byte];
        uint32_t code = encode_entry.first;
        uint8_t length = encode_entry.second;
        for (uint8_t i = 0; i < length; ++i)
        {
            writeBitTooBuffer(code, i);
        }
    }
    //TODO: Replace writeBuffer() with some clean up method
    writeBuffer();
}

void huffman::Encoder::writeBitTooBuffer(uint32_t code, uint8_t length)
{
    std::size_t index = bitsInBuffer_ / constants::BITS_IN_BYTE;
    code = (code & (1 << length)) >> length;
    buffer_[index] |= code << ((constants::BITS_IN_BYTE - 1) - (bitsInBuffer_ % constants::BITS_IN_BYTE));
    ++bitsInBuffer_;
    if (bitsInBuffer_ == (constants::BUFFER_SIZE_BYTES * constants::BITS_IN_BYTE))
    {
        writeBuffer();
    }
}

void huffman::Encoder::writeBuffer()
{
    //TODO: Check if opening the stream failed
    std::ofstream ofstream{fileName_, std::ios_base::app | std::ios::out | std::ios::binary};
    ofstream.write(reinterpret_cast<char *>(&buffer_[0]), bitsInBuffer_ / constants::BITS_IN_BYTE);
    std::memset(&buffer_, 0, sizeof(buffer_));
    bitsInBuffer_ = 0;
}


