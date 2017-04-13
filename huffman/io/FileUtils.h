#ifndef HUFFMANCODING_BINARYFILEREADER_H
#define HUFFMANCODING_BINARYFILEREADER_H

#include <iosfwd>

#include "common/Vector.h"
#include "common/BitStack.h"
#include "../Common.h"

namespace huffman
{
    namespace io
    {
        /**
         * Reads data from the stream and outputs it into vector of bytes.
         * @param istream Stream to read data from.
         * @return Returns vector of bytes containing data from the stream
         */
        common::Vector<huffman::types::byte_t> readFile(std::istream& istream);

        /**
         * Writes data to the specified stream
         * @param ostream Stream to write to
         * @param data Data that is written to the stream
         */
        void writeFile(std::ostream& ostream, const common::Vector<huffman::types::byte_t>& data);

        /**
         * Writes data as binary data to the stream.
         * @param ostream Stream to write to.
         * @param data Data that is written to the stream.
         */
        void writeBinaryFile(std::ostream& ostream, const common::BitStack& data);

        /**
         * Reads data from the stream to vector containing bool values.
         * @param istream Stream to read from.
         * @param ignoreHeader Ignore the header data i.e. usually the HuffmanTree data and read the actual data
         * @return Data read from the stream
         */
        common::BitStack readBinaryFile(std::istream& istream, bool ignoreHeader);

        /**
         * Reads eight bytes from the data and outputs unsigned 64-bit number. First byte in the array is the least significant
         * and the last is the most significant.
         * @param data Eight bytes that represent 64-bit number
         * @return Unsigned 64-bit number
         */
        uint64_t read64BitNumber(const uint8_t (& data)[8]);

        /**
         * Writes 64-bit number to the specified stream as individual bytes. The first byte in the stream represents
         * the least significant byte of the number and the last is the most significant byte.
         * @param number 64-bit number that is written to the stream.
         * @param ostream Stream that is written to.
         */
        void write64BitNumberToStream(uint64_t number, std::ostream& ostream);

        /**
         * Inserts byte to the vector as binary values.
         * @param byte Byte to insert into the vector.
         * @param vector Vector to write into.
         */
        void insertByte(huffman::types::byte_t byte, common::BitStack& vector);

        /**
         * Reads byte from the vector containing binary values starting from the specified index.
         * @param vector Vector to read from
         * @param start Starting index
         * @return Byte read from the vector
         */
        huffman::types::byte_t readByte(const common::BitStack& vector, uint64_t start);
    }
}


#endif //HUFFMANCODING_BINARYFILEREADER_H
