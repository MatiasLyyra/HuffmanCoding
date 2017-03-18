#ifndef HUFFMANCODING_BINARYFILEREADER_H
#define HUFFMANCODING_BINARYFILEREADER_H

#include <vector>

#include "../Common.h"

namespace huffman
{
    namespace io
    {
        std::vector<huffman::types::byte_t> readFile(const char* filename);
    }
}



#endif //HUFFMANCODING_BINARYFILEREADER_H
