#include "FileUtils.h"

#include <fstream>
#include <iterator>
#include <memory>


std::vector<huffman::types::byte_t> huffman::io::readFile(const char* filename)
{
    std::ifstream file{filename, std::ios::binary | std::ios::in};
    if (file.is_open())
    {
        std::streampos fileSize;
        file.seekg(0, std::ios::end);
        fileSize = file.tellg();
        file.seekg(0, std::ios::beg);

        std::unique_ptr<types::byte_t[]> buffer{new unsigned char[fileSize]};
        file.read(reinterpret_cast<char*>(&buffer.get()[0]), fileSize*sizeof(types::byte_t));
        return std::vector<types::byte_t>{buffer.get(), buffer.get() + fileSize*sizeof(types::byte_t)};
    }

    return std::vector<types::byte_t>{};
}
