#include <string>
#include <fstream>
#include <iostream>
#include <cstring>
#include <chrono>

#include "common/Vector.h"
#include "huffman/Common.h"
#include "huffman/io/FileUtils.h"
#include "huffman/HuffmanTree.h"
#include "huffman/Encoder.h"
#include "huffman/Decoder.h"

#include "TimeResults.h"

EncodingResult encode(const std::string& inPath, const std::string& outPath, bool printTree);

DecodingResults decode(const std::string& inPath, const std::string& outPath);

bool parseParameters(int argc, char* const* argv);

void printEncodingTimes(const EncodingResult& result);

void printDecodingTimes(const DecodingResults& result);

static constexpr int MIN_PARAMETERS = 6;
static std::string HELP_MESSAGE = "Encoding: HuffmanCoding encode -in <file> -out <file2> (-v) (-tree)\nDecoding: HuffmanCoding decode -in <file> -out <file2> (-v)";

std::string inPath, outPath;
bool encoding = true;
bool verbose = false;
bool printTree = false;
int benchmark = 0;

int main(int argc, char** argv)
{
    if (!parseParameters(argc, argv))
    {
        std::cerr << "Invalid parameters" << std::endl << HELP_MESSAGE << std::endl;
    }
    else
    {
        int count = std::max(1, benchmark);
        DecodingResults decodingResults;
        decodingResults.success = true;
        EncodingResult encodingResult;
        encodingResult.success = true;

        for (int i = 0; i < count; ++i)
        {
            if (encoding)
            {
                auto result = encode(inPath, outPath, printTree);
                encodingResult.fileReading += result.fileReading;
                encodingResult.huffmanTreeBuilding += result.huffmanTreeBuilding;
                encodingResult.encoding += result.encoding;
                encodingResult.headerWrite += result.headerWrite;
                encodingResult.encodedDataWrite += result.encodedDataWrite;
                encodingResult.total += result.total;
                encodingResult.success = encodingResult.success && result.success;
            } else
            {
                auto result = decode(inPath, outPath);
                decodingResults.fileHeaderRead += result.fileHeaderRead;
                decodingResults.fileDataRead += result.fileDataRead;
                decodingResults.decoding += result.decoding;
                decodingResults.fileWrite += result.fileWrite;
                decodingResults.total += result.total;
                decodingResults.success = decodingResults.success && result.success;
            }
        }
        if (verbose && encodingResult.success && encoding)
        {
            encodingResult.fileReading /= count;
            encodingResult.huffmanTreeBuilding /= count;
            encodingResult.encoding /= count;
            encodingResult.headerWrite /= count;
            encodingResult.encodedDataWrite /= count;
            encodingResult.total /= count;
            printEncodingTimes(encodingResult);
        }
        if (verbose && decodingResults.success  && !encoding)
        {
            decodingResults.fileHeaderRead /= count;
            decodingResults.fileDataRead /= count;
            decodingResults.decoding /= count;
            decodingResults.fileWrite /= count;
            decodingResults.total /= count;
            printDecodingTimes(decodingResults);
        }

    }
    return 0;
}

void printDecodingTimes(const DecodingResults& result)
{
    std::cout << "Header reading:\t" << result.fileHeaderRead << " microseconds" << std::endl;
    std::cout << "Data reading:\t" << result.fileDataRead << " microseconds" << std::endl;
    std::cout << "Decoding:\t" << result.decoding << " microseconds" << std::endl;
    std::cout << "Write time:\t" << result.fileWrite << " microseconds" << std::endl;
    std::cout << "Total:\t\t" << result.total << " microseconds" << std::endl;
}

void printEncodingTimes(const EncodingResult& result)
{
    std::cout << "File reading:\t\t" << result.fileReading << " microseconds""" << std::endl;
    std::cout << "HuffmanTree building:\t" << result.huffmanTreeBuilding << " microseconds" << std::endl;
    std::cout << "Encoding:\t\t" << result.encoding << " microseconds" << std::endl;
    std::cout << "Writing header:\t\t" << result.headerWrite << " microseconds" << std::endl;
    std::cout << "Writing data:\t\t" << result.encodedDataWrite << " microseconds" << std::endl;
    std::cout << "Total:\t\t\t" << result.total << " microseconds" << std::endl;
}

bool parseParameters(int argc, char* const* argv)
{
    if (argc < MIN_PARAMETERS)
    {
        return false;
    }

    if (strcmp(argv[1], "encode") == 0)
    {
        encoding = true;
    } else if (strcmp(argv[1], "decode") == 0)
    {
        encoding = false;
    } else
    {
        return false;
    }

    for (int i = 2; i < argc; ++i)
    {
        if (strcmp(argv[i], "-in") == 0)
        {
            inPath = argv[++i];
        } else if (strcmp(argv[i], "-out") == 0)
        {
            outPath = argv[++i];
        } else if (strcmp(argv[i], "-v") == 0)
        {
            verbose = true;
        } else if (strcmp(argv[i], "-tree") == 0)
        {
            printTree = true;
        }
        else if (strcmp(argv[i], "-benchmark") == 0)
        {
            benchmark = atoi(argv[++i]);
        } else
        {
            return false;
        }
    }
    return true;
}

EncodingResult encode(const std::string& inPath, const std::string& outPath, bool printTree)
{
    EncodingResult result;
    //std::cout << "Encoding data from \"" << inPath << "\" to \"" << outPath << "\"" << std::endl;
    std::ifstream ifstream{inPath, std::ios::binary | std::ios::in};
    if (!ifstream.is_open())
    {
        std::cerr << "Couldn't open file: " << inPath << std::endl;
        return result;
    }

    auto time = std::chrono::system_clock::now();
    common::Vector<huffman::types::byte_t> file{huffman::io::readFile(ifstream)};
    auto readingTime = std::chrono::duration_cast<std::chrono::nanoseconds>(std::chrono::system_clock::now() - time);

    time = std::chrono::system_clock::now();
    huffman::HuffmanTree huffmanTree{file};
    auto huffmanTreeBuildingTime = std::chrono::duration_cast<std::chrono::nanoseconds>(
            std::chrono::system_clock::now() - time);

    time = std::chrono::system_clock::now();
    huffman::Encoder encoder;
    encoder.createHeader(huffmanTree);
    encoder.encodeData(huffmanTree.constructEncodingTable(), file);
    auto encodingTime = std::chrono::duration_cast<std::chrono::nanoseconds>(std::chrono::system_clock::now() - time);

    std::ofstream ofstream{outPath, std::ios::binary | std::ios::out};
    if (!ofstream.is_open())
    {
        std::cerr << "Couldn't write to file: " << outPath << std::endl;
        return result;
    }

    time = std::chrono::system_clock::now();
    huffman::io::writeBinaryFile(ofstream, encoder.getHeaderData());
    auto headerWriteTime = std::chrono::duration_cast<std::chrono::nanoseconds>(
            std::chrono::system_clock::now() - time);

    ofstream.close();
    ofstream.open(outPath, std::ios::binary | std::ios::out | std::ios::app);
    if (!ofstream.is_open())
    {
        std::cerr << "Couldn't write to file: " << outPath << std::endl;
        return result;
    }
    time = std::chrono::system_clock::now();
    huffman::io::writeBinaryFile(ofstream, encoder.getEncodedData());
    auto encodedDataWriteTime = std::chrono::duration_cast<std::chrono::nanoseconds>(
            std::chrono::system_clock::now() - time);

    if (printTree)
    {
        huffmanTree.printTree(std::cout);
    }

    result.fileReading = readingTime.count();
    result.huffmanTreeBuilding = huffmanTreeBuildingTime.count();
    result.encoding = encodingTime.count();
    result.headerWrite = headerWriteTime.count();
    result.encodedDataWrite = encodedDataWriteTime.count();
    auto total = readingTime + huffmanTreeBuildingTime + encodingTime + headerWriteTime + encodedDataWriteTime;
    result.total = total.count();
    result.success = true;

    return result;
}

DecodingResults decode(const std::string& inPath, const std::string& outPath)
{
    DecodingResults result;
    //std::cout << "Decoding data from \"" << inPath << "\" to \"" << outPath << "\"" << std::endl;
    std::ifstream ifstream{inPath, std::ios::binary | std::ios::in};
    if (!ifstream.is_open())
    {
        std::cerr << "Couldn't open file: " << inPath << std::endl;
        return result;
    }

    auto time = std::chrono::system_clock::now();
    common::BitStack encodedTree{huffman::io::readBinaryFile(ifstream, false)};
    auto headerReadTime = std::chrono::duration_cast<std::chrono::nanoseconds>(
            std::chrono::system_clock::now() - time);

    ifstream.close();
    ifstream.open(inPath, std::ios::binary | std::ios::in);
    if (!ifstream.is_open())
    {
        std::cerr << "Couldn't open file: " << inPath << std::endl;
        return result;
    }

    time = std::chrono::system_clock::now();
    common::BitStack encodedData{huffman::io::readBinaryFile(ifstream, true)};
    auto dataReadTime = std::chrono::duration_cast<std::chrono::nanoseconds>(std::chrono::system_clock::now() - time);

    huffman::Decoder decoder;

    time = std::chrono::system_clock::now();
    decoder.decodeData(encodedTree, encodedData);
    auto decodingTime = std::chrono::duration_cast<std::chrono::nanoseconds>(std::chrono::system_clock::now() - time);

    std::ofstream ofstream{outPath, std::ios::binary | std::ios::out};
    if (!ofstream.is_open())
    {
        std::cerr << "Couldn't write to file: " << outPath << std::endl;
        return result;
    }
    time = std::chrono::system_clock::now();
    huffman::io::writeFile(ofstream, decoder.getDecodedData());
    auto fileWriteTime = std::chrono::duration_cast<std::chrono::nanoseconds>(std::chrono::system_clock::now() - time);

    result.fileHeaderRead = headerReadTime.count();
    result.fileDataRead = dataReadTime.count();
    result.decoding = decodingTime.count();
    result.fileWrite = fileWriteTime.count();
    auto total = headerReadTime + dataReadTime + decodingTime + fileWriteTime;
    result.total = total.count();
    result.success = true;

    return result;
}