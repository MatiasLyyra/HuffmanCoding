#ifndef HUFFMANCODING_DECODER_H
#define HUFFMANCODING_DECODER_H

#include <string>
#include <vector>
#include "Common.h"

namespace huffman
{
    class TreeNode;
    class Decoder
    {
    public:
        explicit Decoder(const std::string& filename);
        std::vector<huffman::types::byte_t> decode(const huffman::TreeNode &root);

    private:
        std::string filename_;
    };
}



#endif //HUFFMANCODING_DECODER_H
