#ifndef HUFFMANCODING_ENCODER_H
#define HUFFMANCODING_ENCODER_H

#include <vector>
#include <string>

#include "Common.h"

namespace huffman
{
    class Encoder {

    public:
        explicit Encoder(const std::string& fileName);
        void encodeData(const types::encode_table_t& encode_table, const std::vector<types::byte_t>& data);

    private:
        void writeBitTooBuffer(uint32_t code, uint8_t length);
        void writeBuffer();

        types::byte_t buffer_[constants::BUFFER_SIZE_BYTES];
        uint64_t bitsInBuffer_;
        std::string fileName_;
    };
}



#endif //HUFFMANCODING_ENCODER_H
