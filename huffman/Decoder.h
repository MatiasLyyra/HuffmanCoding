#ifndef HUFFMANCODING_DECODER_H
#define HUFFMANCODING_DECODER_H

#include <vector>

#include "Common.h"

namespace huffman
{
    class TreeNode;

    /**
     * Class responsible for decoding given envcoded data.
     */
    class Decoder
    {
    public:

        Decoder();

        /**
         * Decodes the given encoded data. Decoded data can be read from getDecodedData().
         * @param treeInBinary Binary representation of HuffmanTree
         * @param encodedData Encoded data which is decoded
         */
        void decode(const std::vector<bool>& treeInBinary, const std::vector<bool>& encodedData);

        const std::vector<huffman::types::byte_t>& getDecodedData() const;

    private:
        std::vector<huffman::types::byte_t> decodedData_;
    };
}


#endif //HUFFMANCODING_DECODER_H
