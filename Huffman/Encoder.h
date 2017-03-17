//
// Created by Matias-PC on 16.3.2017.
//

#ifndef HUFFMANCODING_ENCODER_H
#define HUFFMANCODING_ENCODER_H

#include <vector>

#include "Common.h"

namespace huffman
{
    class Encoder {
    public:
        void encodeData(const types::encode_table_t& encode_table, const std::vector<unsigned char>& data);

    private:
        std::vector<bool> encodedData_;
    };
}



#endif //HUFFMANCODING_ENCODER_H
