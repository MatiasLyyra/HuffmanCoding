#ifndef HUFFMANCODING_ENCODER_H
#define HUFFMANCODING_ENCODER_H

#include <vector>
#include <string>

#include "Common.h"

namespace huffman
{
    class TreeNode;

    /**
     * Class responsible for creating binary representation of the HuffmanTree and encoding messages.
     */
    class Encoder
    {

    public:
        Encoder();

        /**
         * Creates binary representation of the HuffmanTree. Encoded tree can be read from getEncodedData().
         * @param root Root of the HuffmanTree.
         */
        void createHeader(const huffman::TreeNode& root);

        /**
         * Encodes given data based on encoding table. Encoded data can be read with getEncodedData().
         * @param encode_table Encode table that is used to encode the data.
         * @param data Data to be encoded
         * @throw Throws std::invalid_argument exception if character is encountered without proper value in encoding table
         * i.e. any encode entry with length of zero.
         */
        void encodeData(const types::encode_table_t& encode_table, const std::vector<types::byte_t>& data);

        const std::vector<bool>& getHeaderData() const;

        const std::vector<bool>& getEncodedData() const;


    private:
        std::vector<bool> headerData_;
        std::vector<bool> encodedData_;
    };
}


#endif //HUFFMANCODING_ENCODER_H
