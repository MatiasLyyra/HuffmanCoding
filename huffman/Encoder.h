#ifndef HUFFMANCODING_ENCODER_H
#define HUFFMANCODING_ENCODER_H

#include <string>

#include "common/BitStack.h"
#include "common/Vector.h"
#include "Common.h"
#include "HuffmanTree.h"

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
         * @param huffmanTree HuffmanTree.
         */
        void createHeader(const huffman::HuffmanTree& huffmanTree);

        /**
         * Encodes given data based on encoding table. Encoded data can be read with getEncodedData().
         * @param encode_table Encode table that is used to encode the data.
         * @param data Data to be encoded
         * @throw Throws std::invalid_argument exception if character is encountered without proper value in encoding table
         * i.e. any encode entry with length of zero.
         */
        void encodeData(const types::encode_table_t& encode_table, const common::Vector<types::byte_t>& data);

        const common::BitStack& getHeaderData() const;

        const common::BitStack& getEncodedData() const;


    private:
        common::BitStack headerData_;
        common::BitStack encodedData_;
    };
}


#endif //HUFFMANCODING_ENCODER_H
