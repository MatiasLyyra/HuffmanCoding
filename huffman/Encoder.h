#ifndef HUFFMANCODING_ENCODER_H
#define HUFFMANCODING_ENCODER_H

#include <vector>
#include <string>

#include "Common.h"

namespace huffman
{
    class TreeNode;
    class Encoder {

    public:
        Encoder();
        void createHeader(const huffman::TreeNode& root);
        void encodeData(const types::encode_table_t& encode_table, const std::vector<types::byte_t>& data);
        const std::vector<bool>& getHeaderData() const;
        const std::vector<bool>& getEncodedData() const;


    private:
        std::vector<bool> headerData_;
        std::vector<bool> encodedData_;
    };
}



#endif //HUFFMANCODING_ENCODER_H
