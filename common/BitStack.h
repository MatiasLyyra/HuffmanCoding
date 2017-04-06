#ifndef HUFFMANCODING_BITVECTOR_H
#define HUFFMANCODING_BITVECTOR_H

#include "Vector.h"

namespace common
{
    class BitStack
    {
    public:
        using size_type = std::size_t;

        BitStack();

        void push_back(bool value);

        void push_back(uint32_t value, uint8_t length);

        void pop_back() noexcept;

        void reserve(size_type amount);

        bool operator[](size_type index) const;

        bool at(size_type index) const;

        bool empty() const noexcept;

        bool clear() noexcept;

        Vector<uint32_t>::size_type container_size() const noexcept;

        size_type size() const noexcept;

        size_type capacity() const noexcept;

        uint32_t* data() noexcept;

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
