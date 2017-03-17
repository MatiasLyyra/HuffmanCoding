//
// Created by Matias-PC on 16.3.2017.
//

#ifndef HUFFMANCODING_BINARYFILEREADER_H
#define HUFFMANCODING_BINARYFILEREADER_H

#include <vector>

namespace huffman
{
    namespace io
    {
        std::vector<unsigned char> readFile(const char* filename);
    }
}



#endif //HUFFMANCODING_BINARYFILEREADER_H
