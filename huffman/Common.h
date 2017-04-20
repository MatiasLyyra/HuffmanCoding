#ifndef HUFFMANCODING_CONSTANTS_H
#define HUFFMANCODING_CONSTANTS_H

#include <array>

namespace huffman
{
    namespace constants
    {
        /**
         * Magic number for identifying encoded files.
         */
        static constexpr uint64_t MAGIG_NUMBER = 0x45311e06bdb91029;

        /**
         * Number of different possible characters.
         */
        static constexpr unsigned CHARACTERS = 256;

        /**
         * Maximum length of the encoded character code
         */
        static constexpr unsigned MAX_CODE_LENGTH = 32;
        static constexpr unsigned char BITS_IN_BYTE = 8;
        static constexpr int empty_handle = -1;
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

        /**
         * Handle for accessing specific TreeNode
         */
        using handle_t = int;

        using byte_t = unsigned char;
    }
}
#endif //HUFFMANCODING_CONSTANTS_H
