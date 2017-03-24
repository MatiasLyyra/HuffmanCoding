#ifndef HUFFMANCODING_CONSTANTS_H
#define HUFFMANCODING_CONSTANTS_H

#include <array>

namespace huffman
{
    namespace constants
    {
        /**
         * Number of different possible characters.
         */
        constexpr unsigned CHARACTERS = 256;

        /**
         * Maximum length of the encoded character code
         */
        constexpr unsigned MAX_CODE_LENGTH = 32;
        static constexpr unsigned char BITS_IN_BYTE = 8;
    }
    namespace types
    {
        /**
         * Encoded character where the first value represents the encoded character value and second value the length
         * of the first value
         */
        using encode_entry_t = std::pair<uint32_t, uint8_t>;

        /**
         * Array that is used to encode bytes. Index of the cell represents the byte/character.
         */
        using encode_table_t = std::array<encode_entry_t, constants::CHARACTERS>;
        using byte_t = unsigned char;
    }
}
#endif //HUFFMANCODING_CONSTANTS_H
