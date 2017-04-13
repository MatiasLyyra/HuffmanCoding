#include <string>
#include <fstream>
#include <iostream>
#include <cstring>
#include <chrono>

#include "common/Vector.h"
#include "huffman/Common.h"
#include "io/FileUtils.h"
#include "huffman/HuffmanTree.h"
#include "huffman/Encoder.h"
#include "huffman/Decoder.h"

void encode(const std::string &inPath, const std::string &outPath, bool printTimes);
void decode(const std::string &inPath, const std::string &outPath, bool printTimes);

int main(int argc,  char** argv)
{
    if (argc == 4)
    {
        if (std::strcmp(argv[1], "encode") == 0)
        {
            encode(argv[2], argv[3], true);
        }
        else if (std::strcmp(argv[1], "decode") == 0)
        {
            decode(argv[2], argv[3], true);
        }
    }
    else
    {
        std::cout << "Wrong number of parameters!" << std::endl
                  << "Encoding: HuffmanCoding encode <input> <output>" << std::endl
                  << "Decoding: HuffmanCoding decode <input> <output>" << std::endl;
    }
    return 0;
}

void encode(const std::string &inPath, const std::string &outPath, bool printTimes)
{
    std::cout << "Encoding data from \"" << inPath << "\" to \"" << outPath << "\"" << std::endl;
    std::ifstream ifstream{inPath, std::ios::binary | std::ios::in};
    if (!ifstream.is_open())
    {
        std::cerr << "Couldn't open file: " << inPath << std::endl;
        return;
    }

    auto time = std::chrono::system_clock::now();
    common::Vector<huffman::types::byte_t> file{huffman::io::readFile(ifstream)};
    auto readingTime = std::chrono::duration_cast<std::chrono::microseconds>(std::chrono::system_clock::now() - time);

    time = std::chrono::system_clock::now();
    huffman::HuffmanTree huffmanTree{file};
    auto huffmanTreeBuildingTime = std::chrono::duration_cast<std::chrono::microseconds>(std::chrono::system_clock::now() - time);

    huffmanTree.printTree(std::cout);

    time = std::chrono::system_clock::now();
    huffman::Encoder encoder;
    encoder.createHeader(huffmanTree);
    encoder.encodeData(huffmanTree.constructEncodingTable(), file);
    auto encodingTime = std::chrono::duration_cast<std::chrono::microseconds>(std::chrono::system_clock::now() - time);

    std::ofstream ofstream{outPath, std::ios::binary | std::ios::out};
    if (!ofstream.is_open())
    {
        std::cerr << "Couldn't write to file: " << outPath << std::endl;
        return;
    }

    time = std::chrono::system_clock::now();
    huffman::io::writeBinaryFile(ofstream, encoder.getHeaderData());
    auto headerWriteTime = std::chrono::duration_cast<std::chrono::microseconds>(std::chrono::system_clock::now() - time);

    ofstream.close();
    ofstream.open(outPath, std::ios::binary | std::ios::out | std::ios::app);
    if (!ofstream.is_open())
    {
        std::cerr << "Couldn't write to file: " << outPath << std::endl;
        return;
    }
    time = std::chrono::system_clock::now();
    huffman::io::writeBinaryFile(ofstream, encoder.getEncodedData());
    auto encodedDataWriteTime = std::chrono::duration_cast<std::chrono::microseconds>(std::chrono::system_clock::now() - time);

    if (printTimes)
    {
        std::cout << "File reading:\t\t" << readingTime.count() << " microseconds""" << std::endl;
        std::cout << "HuffmanTree building:\t" << huffmanTreeBuildingTime.count() << " microseconds" << std::endl;
        std::cout << "Encoding:\t\t" << encodingTime.count() << " microseconds" << std::endl;
        std::cout << "Writing header:\t\t" << headerWriteTime.count() << " microseconds" << std::endl;
        std::cout << "Writing data:\t\t" << encodedDataWriteTime.count() << " microseconds" << std::endl;
        auto total = readingTime + huffmanTreeBuildingTime + encodingTime + headerWriteTime + encodedDataWriteTime;
        std::cout << "Total:\t\t\t" << total.count() << " microseconds" << std::endl;
    }
}

void decode(const std::string &inPath, const std::string &outPath, bool printTimes)
{
    std::cout << "Decoding data from \"" << inPath << "\" to \"" << outPath << "\"" << std::endl;
    std::ifstream ifstream{inPath, std::ios::binary | std::ios::in};
    if (!ifstream.is_open())
    {
        std::cerr << "Couldn't open file: " << inPath << std::endl;
        return;
    }

    auto time = std::chrono::system_clock::now();
    common::BitStack encodedTree{huffman::io::readBinaryFile(ifstream, false)};
    auto headerReadTime = std::chrono::duration_cast<std::chrono::microseconds>(std::chrono::system_clock::now() - time);

    ifstream.close();
    ifstream.open(inPath, std::ios::binary | std::ios::in);
    if (!ifstream.is_open())
    {
        std::cerr << "Couldn't open file: " << inPath << std::endl;
        return;
    }

    time = std::chrono::system_clock::now();
    common::BitStack encodedData{huffman::io::readBinaryFile(ifstream, true)};
    auto dataReadTime = std::chrono::duration_cast<std::chrono::microseconds>(std::chrono::system_clock::now() - time);

    huffman::Decoder decoder;

    time = std::chrono::system_clock::now();
    decoder.decodeData(encodedTree, encodedData);
    auto decodingTime = std::chrono::duration_cast<std::chrono::microseconds>(std::chrono::system_clock::now() - time);

    std::ofstream ofstream{outPath, std::ios::binary | std::ios::out};
    if (!ofstream.is_open())
    {
        std::cerr << "Couldn't write to file: " << outPath << std::endl;
        return;
    }
    time = std::chrono::system_clock::now();
    huffman::io::writeFile(ofstream, decoder.getDecodedData());
    auto fileWriteTime = std::chrono::duration_cast<std::chrono::microseconds>(std::chrono::system_clock::now() - time);

    if (printTimes)
    {
        std::cout << "Header reading:\t" << headerReadTime.count() << " microseconds" << std::endl;
        std::cout << "Data reading:\t" << dataReadTime.count() << " microseconds" << std::endl;
        std::cout << "Decoding:\t" << decodingTime.count() << " microseconds" << std::endl;
        std::cout << "Write time:\t" << fileWriteTime.count() << " microseconds" << std::endl;
        auto total = headerReadTime + dataReadTime + decodingTime + fileWriteTime;
        std::cout << "Total:\t\t" << total.count() << " microseconds" << std::endl;
    }
}