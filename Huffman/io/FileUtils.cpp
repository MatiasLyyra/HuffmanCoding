//
// Created by Matias-PC on 16.3.2017.
//

#include "FileUtils.h"

#include <fstream>
#include <iterator>
#include <bits/unique_ptr.h>


std::vector<unsigned char> huffman::io::readFile(const char* filename)
{
    std::ifstream file{filename, std::ios::binary | std::ios::in};
    if (file.is_open())
    {
        std::streampos fileSize;
        file.seekg(0, std::ios::end);
        fileSize = file.tellg();
        file.seekg(0, std::ios::beg);
        std::unique_ptr<unsigned char[]> buffer{new unsigned char[fileSize]};
        file.read(reinterpret_cast<char*>(&buffer.get()[0]), fileSize*sizeof(unsigned char));
        return std::vector<unsigned char>{buffer.get(), buffer.get() + fileSize*sizeof(unsigned char)};
    }

    return std::vector<unsigned char>{};
}
