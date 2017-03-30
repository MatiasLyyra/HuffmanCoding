#ifndef HUFFMANCODING_VECTOR_H
#define HUFFMANCODING_VECTOR_H

#include <cassert>
#include <cstddef>
#include <memory>

namespace common
{
    template<class T>
    class Vector
    {
    public:
        using size_type = std::size_t;
        using iterator = T*;
        using const_iterator = const T*;
        using reference = T&;
        using const_reference = const T&;

        Vector();
        explicit Vector(size_type size, T const& defaultValue = T{});
        Vector(Vector<T> const &other);
        Vector(iterator start, iterator end);
        Vector<T>& operator=(Vector<T> other);
        Vector(Vector<T> &&other) = default;
        Vector<T>& operator=(Vector<T> &&other) = default;
        ~Vector()
        {
            clear();
        }
        void reserve(size_type new_size);
        void swap(Vector<T> &other) noexcept;

        void push_back(T const &value);
        void pop_back() noexcept;
        void insert(size_type position, T const& value);
        void insert(size_type position, size_type n, T const& value);
        void insert(Vector<T> const &other, size_type start, size_type end);

        void clear() noexcept;

        reference operator[] (size_type index)
        {
            if (empty() || index >= size_)
            {
                throw std::out_of_range("Index out of bounds");
            }
            iterator it = begin();
            return it[index];
        }

        const_reference operator[] (size_type index) const
        {
            if (empty() || index >= size_)
            {
                throw std::out_of_range("Index out of bounds");
            }
            auto it = begin();
            return it[index];
        }

        reference at(size_type index)
        {
            return (*this)[index];
        }

        const_reference at(size_type index) const
        {
            return (*this)[index];
        }

        reference front()
        {
            return (*this)[0];
        }

        const_reference front() const
        {
            return (*this)[0];
        }

        reference back()
        {
            return (*this)[size_ - 1];
        }

        const_reference back() const
        {
            return (*this)[size_ - 1];
        }

        iterator begin() noexcept
        {
            return reinterpret_cast<iterator>(data_.get());
        }

        iterator end() noexcept
        {
            return reinterpret_cast<iterator>(data_.get() + (size_ * sizeof(T)));
        }

        const_iterator begin() const noexcept
        {
            return reinterpret_cast<const_iterator>(data_.get());
        }

        const_iterator end() const noexcept
        {
            return reinterpret_cast<const_iterator>(data_.get() + (size_ * sizeof(T)));
        }

        size_type size() const noexcept
        {
            return size_;
        }

        size_type capacity() const noexcept
        {
            return capacity_;
        }

        bool empty() const noexcept
        {
            return size_ == 0;
        }

    private:
        static constexpr float RESERVE_MULTIPLIER = 1.5;
        size_type size_;
        size_type capacity_;
        std::unique_ptr<char[]> data_;
    };

#include "Vector.tcc"
}

#endif //HUFFMANCODING_VECTOR_H
