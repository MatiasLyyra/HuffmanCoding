//
// Created by Matias-PC on 16.3.2017.
//
#include <cassert>
#include <cstdint>

#include "Encoder.h"

void huffman::Encoder::encodeData(const huffman::types::encode_table_t &encode_table, const std::vector<unsigned char>& data)
{
    assert(encode_table.size() == constants::CHARACTERS);
    encodedData_.reserve(data.size());

    for (auto byte : data)
    {
        types::encode_entry_t encode_entry = encode_table[byte];
        uint32_t code = encode_entry.first;
        uint8_t length = encode_entry.second;
        for (int i = 0; i < length; ++i) {
            bool bit = ((1 << i) & code) == 1 << i;
            encodedData_.push_back(bit);
        }
    }
}
