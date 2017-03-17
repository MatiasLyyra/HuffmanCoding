//
// Created by Matias-PC on 16.3.2017.
//

#ifndef HUFFMANCODING_CONSTANTS_H
#define HUFFMANCODING_CONSTANTS_H

#include <array>

namespace huffman
{
    namespace constants
    {
        constexpr unsigned CHARACTERS = 256;
        constexpr unsigned MAX_CODE_LENGTH = 32;
    }
    namespace types
    {
        // First value is the actual code of the entry
        // Second value is the length of the code
        using encode_entry_t = std::pair<uint32_t, uint8_t>;
        using encode_table_t = std::array<encode_entry_t, constants::CHARACTERS>;
    }
}
#endif //HUFFMANCODING_CONSTANTS_H
