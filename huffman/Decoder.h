#ifndef HUFFMANCODING_DECODER_H
#define HUFFMANCODING_DECODER_H

#include <vector>

#include "Common.h"

namespace huffman
{
    class TreeNode;
    class Decoder
    {
    public:
        Decoder();
        void decode(const std::vector<bool>& treeInBinary, const std::vector<bool>& encodedData);

        const std::vector<huffman::types::byte_t>& getDecodedData() const;

    private:
        std::vector<huffman::types::byte_t> decodedData_;
    };
}



#endif //HUFFMANCODING_DECODER_H
