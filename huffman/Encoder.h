#ifndef HUFFMANCODING_ENCODER_H
#define HUFFMANCODING_ENCODER_H

#include <vector>
#include <string>

#include "Common.h"
#include "io/FileBuffer.h"

namespace huffman
{
    class TreeNode;
    class Encoder {

    public:
        explicit Encoder(const std::string& fileName);
        void createHeader(const huffman::TreeNode& root);
        void encodeData(const types::encode_table_t& encode_table, const std::vector<types::byte_t>& data);

    private:
        std::string filename_;
    };
}



#endif //HUFFMANCODING_ENCODER_H
