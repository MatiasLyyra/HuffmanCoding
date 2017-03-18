#ifndef HUFFMANCODING_CONSTANTS_H
#define HUFFMANCODING_CONSTANTS_H

#include <array>

namespace huffman
{
    namespace constants
    {
        constexpr unsigned CHARACTERS = 256;
        constexpr unsigned MAX_CODE_LENGTH = 32;
        static constexpr unsigned char BITS_IN_BYTE = 8;
        static constexpr unsigned BUFFER_SIZE_BYTES = 1024 * 50;
    }
    namespace types
    {
        // First value is the actual code of the entry
        // Second value is the length of the code
        using encode_entry_t = std::pair<uint32_t, uint8_t>;
        using encode_table_t = std::array<encode_entry_t, constants::CHARACTERS>;
        using byte_t = unsigned char;
    }
}
#endif //HUFFMANCODING_CONSTANTS_H
