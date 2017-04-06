#include <string>
#include <fstream>
#include <iostream>
#include <cstring>

#include "Vector.h"
#include "Common.h"
#include "io/FileUtils.h"
#include "HuffmanTree.h"
#include "Encoder.h"
#include "Decoder.h"

bool encode(const std::string &inPath, const std::string &outPath);
bool decode(const std::string &inPath, const std::string &outPath);

int main(int argc,  char** argv)
{
    if (argc == 4)
    {
        if (std::strcmp(argv[1], "encode") == 0)
        {
            encode(argv[2], argv[3]);
        }
        else if (std::strcmp(argv[1], "decode") == 0)
        {
            decode(argv[2], argv[3]);
        }
    }
    else
    {
        std::cout << "Wrong number of parameters!" << std::endl
                  << "Encoding: HuffmanCoding encode <input> <output>" << std::endl
                  << "Decoding: HuffmanCoding decode <input> <output>" << std::endl;
    }
}

bool encode(const std::string &inPath, const std::string &outPath)
{
    std::cout << "Encoding data from \"" << inPath << "\" to \"" << outPath << "\"" << std::endl;
    std::ifstream ifstream{inPath, std::ios::binary | std::ios::in};
    if (ifstream.is_open())
    {
        common::Vector<huffman::types::byte_t> file{huffman::io::readFile(ifstream)};
        huffman::HuffmanTree huffmanTree{file};
        huffman::Encoder encoder;
        encoder.createHeader(huffmanTree);
        encoder.encodeData(huffmanTree.constructEncodingTable(), file);

        std::ofstream ofstream{outPath, std::ios::binary | std::ios::out};
        huffman::io::writeBinaryFile(ofstream, encoder.getHeaderData());
        ofstream.close();
        ofstream.open(outPath, std::ios::binary | std::ios::out | std::ios::app);
        huffman::io::writeBinaryFile(ofstream, encoder.getEncodedData());
        std::cout << "Done!" << std::endl;
        return true;
    }
    return false;
}

bool decode(const std::string &inPath, const std::string &outPath)
{
    std::cout << "Decoding data from \"" << inPath << "\" to \"" << outPath << "\"" << std::endl;
    std::ifstream ifstream{inPath, std::ios::binary | std::ios::in};
    if (ifstream.is_open())
    {
        std::vector<bool> encodedTree{huffman::io::readBinaryFile(ifstream, false)};
        ifstream.close();
        ifstream.open(inPath, std::ios::binary | std::ios::in);
        std::vector<bool> encodedData{huffman::io::readBinaryFile(ifstream, true)};
        huffman::Decoder decoder;
        decoder.decodeData(encodedTree, encodedData);

        std::ofstream ofstream{outPath, std::ios::binary | std::ios::out};
        huffman::io::writeFile(ofstream, decoder.getDecodedData());
        return true;
    }
    return false;
}
