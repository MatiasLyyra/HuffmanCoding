#ifndef HUFFMANCODING_BITVECTOR_H
#define HUFFMANCODING_BITVECTOR_H

#include "Vector.h"

namespace common
{
    /**
     * Stack data structure for holding binary data efficiently.
     */
    class BitStack
    {
    public:
        using size_type = std::size_t;

        /**
         * Constructs empty BitStack
         */
        BitStack();

        /**
         * Inserts value at the end of the stack.
         * @param value Value to insert.
         */
        void push_back(bool value);

        /**
         * Inserts values to the end of the stack. Parameter value is handled as a string of binary values.
         * Length signifies how many bits of the value are included starting from the least significant bit.
         * @param value String of bits to insert
         * @param length Amount of bits inserted starting from the least significant bit.
         * @throw std::illegal_argument if length is zero or greater than 32.
         */
        void push_back(uint32_t value, uint8_t length);

        /**
         * Removes the last bit in the stack.
         */
        void pop_back() noexcept;

        /**
         * Reserves space for at least specified amount of bits.
         * @param amount
         */
        void reserve(size_type amount);

        /**
         * Provides access to individual bit value in the stack
         * @param index Index of the bit
         * @return Value of the bit
         */
        bool operator[](size_type index) const;

        /**
        * Provides access to individual bit value in the stack
        * @param index Index of the bit
        * @return Value of the bit
        */
        bool at(size_type index) const;

        /**
         * Returns the value of the bit on top of the stack
         * @return Value of the bit.
         */
        bool top() const;

        /**
         * Returns true if the stack is empty, otherwise false.
         * @return True if the stack is empty, otherwise false.
         */
        bool empty() const noexcept;

        /**
         * Clears the whole stack.
         */
        void clear() noexcept;

        /**
         * Returns the true size of the underlying container.
         * @return Size of the container.
         */
        Vector<uint32_t>::size_type container_size() const noexcept;

        /**
         * Size of the stack.
         * @return Size of the stack.
         */
        size_type size() const noexcept;

        /**
         * Capacity of the stack
         * @return Capacity of the stack.
         */
        size_type capacity() const noexcept;

        /**
         * Pointer to the data of the stack.
         * @return Pointer to the data.
         */
        uint32_t* data() noexcept;

        /**
         * Pointer to the data of the stack.
         * @return Pointer to the data.
         */
        const uint32_t* data() const noexcept;

    private:
        size_type getIndexInWord(const size_type& i) const;

        uint32_t clearValue(uint32_t value, uint8_t length);

        void ensureCapacity();

        static constexpr unsigned BITS_IN_WORD = 32;

        size_type size_;
        Vector<uint32_t> data_;
    };
}


#endif //HUFFMANCODING_BITVECTOR_H
