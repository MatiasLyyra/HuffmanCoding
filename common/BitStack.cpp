#include "BitStack.h"

common::BitStack::BitStack()
        : size_{0},
          data_{5, 0u}
{

}

void common::BitStack::push_back(bool value)
{
    size_type index = size_ / BITS_IN_WORD;
    uint32_t binary_data = data_[index];
    uint32_t value_to_insert = value ? 1u : 0u;
    binary_data |= value_to_insert << (getIndexInWord(size_));
    data_[index] = binary_data;
    ++size_;
    ensureCapacity();
}

void common::BitStack::push_back(uint32_t value, uint8_t length)
{
    if (length > BITS_IN_WORD || length == 0)
    {
        throw std::invalid_argument("Invalid length");
    }
    value = clearValue(value, length);
    size_type available_bits = getIndexInWord(size_) + 1;
    if (available_bits < length)
    {
        data_.push_back(0u);
        size_type first_part_length = available_bits;
        size_type second_part_length = length - first_part_length;
        uint32_t first_part = (value >> second_part_length);
        data_[size_/BITS_IN_WORD] |= first_part;
        size_ += first_part_length;

        uint32_t second_part = value << (BITS_IN_WORD - second_part_length);
        data_[size_/BITS_IN_WORD] = second_part;
        size_ += second_part_length;
    }
    else
    {
        uint32_t binary_data = value << (available_bits - length);
        data_[size_/BITS_IN_WORD] |= binary_data;
        size_ += length;
    }

    ensureCapacity();
}

uint32_t common::BitStack::clearValue(uint32_t value, uint8_t length)
{
    if (length == BITS_IN_WORD)
    {
        return value;
    }
    uint32_t mask = (1u << length) - 1u;
    return value & mask;
}

void common::BitStack::ensureCapacity()
{
    if (size_/BITS_IN_WORD == data_.size())
    {
        data_.push_back(0u);
    }
}

common::BitStack::size_type common::BitStack::getIndexInWord(const size_type &i) const
{
    return common::BitStack::BITS_IN_WORD - (i % common::BitStack::BITS_IN_WORD) - 1;
}

void common::BitStack::pop_back() noexcept
{
    if (!empty())
    {
        size_type bit_index = getIndexInWord(size_ - 1);
        data_[size_/BITS_IN_WORD] &= ~(1 << bit_index);
        --size_;
    }
}

void common::BitStack::reserve(common::BitStack::size_type amount)
{
    data_.reserve(amount / BITS_IN_WORD + 1);
}

bool common::BitStack::operator[](common::BitStack::size_type index) const
{
    if (empty() || index >= size_)
    {
        throw std::invalid_argument("Index out of bounds");
    }
    uint32_t binary_data = data_[index/BITS_IN_WORD];
    size_type bit_index = getIndexInWord(index);
    return (binary_data & (1 << bit_index)) != 0;
}

bool common::BitStack::at(common::BitStack::size_type index) const
{
    return (*this)[index];
}

bool common::BitStack::empty() const noexcept
{
    return size_ == 0;
}

common::BitStack::size_type common::BitStack::size() const noexcept
{
    return size_;
}

common::BitStack::size_type common::BitStack::capacity() const noexcept
{
    return data_.capacity() * BITS_IN_WORD;
}

void common::BitStack::clear() noexcept
{
    size_ = 0;
    data_.clear();
}

uint32_t* common::BitStack::data() noexcept
{
    return data_.begin();
}

const uint32_t* common::BitStack::data() const noexcept
{
    return data_.begin();
}

common::Vector<uint32_t>::size_type common::BitStack::container_size() const noexcept
{
    return 1 + ((size_ - 1) / BITS_IN_WORD);
}

bool common::BitStack::top() const
{
    return (*this)[size_ - 1];
}

