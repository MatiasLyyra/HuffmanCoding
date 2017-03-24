#ifndef HUFFMANCODING_BINARYFILEREADER_H
#define HUFFMANCODING_BINARYFILEREADER_H

#include <vector>
#include <iosfwd>
#include "../Common.h"

namespace huffman
{
    namespace io
    {
        std::vector<huffman::types::byte_t> readFile(std::istream& istream);
        void writeFile(std::ostream& ostream, const std::vector<huffman::types::byte_t>& data);
        void writeBinaryFile(std::ostream& ostream, const std::vector<bool> &data);
        std::vector<bool> readBinaryFile(std::istream& istream, bool ignoreHeader);
        uint64_t read64BitNumber(const uint8_t (&data)[8]);
        void write64BitNumberToStream(uint64_t number, std::ostream &ostream);

        void insertByte(huffman::types::byte_t byte, std::vector<bool>& vector);
        huffman::types::byte_t readByte(const std::vector<bool>& treeInBinary, uint64_t start);
    }
}



#endif //HUFFMANCODING_BINARYFILEREADER_H
