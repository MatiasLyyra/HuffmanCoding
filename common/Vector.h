#ifndef HUFFMANCODING_VECTOR_H
#define HUFFMANCODING_VECTOR_H

#include <cassert>
#include <cstddef>
#include <cstring>
#include <memory>

namespace common
{
    template<class T>
    class Vector
    {
    public:
        using size_type = std::size_t;
        using iterator = T*;
        using const_iterator = T const*;
        using reference = T&;
        using const_reference = T const&;

        /**
         * Constructs empty vector
         */
        Vector();

        /**
         * Constructs vector with specified size and and initializes them with defaultValue
         * @param size Size of the vector
         * @param defaultValue Value that is used to initialize the elements in the vector
         */
        explicit Vector(size_type size, const_reference defaultValue = T{});

        Vector(Vector<T> const& other);

        /**
         * Constructs vector from values in the iterator range
         * @param start Starting point of the iterator range (inclusive)
         * @param end Ending point of the iterator range (exclusive)
         */
        Vector(iterator start, iterator end);

        Vector<T>& operator=(Vector<T> other);

        Vector(Vector<T>&& other) = default;

        Vector<T>& operator=(Vector<T>&& other) = default;

        ~Vector()
        {
            clear();
        }

        /**
         * Allocates space for elements to fit at lest specified number of elements. Reallocation only happens if
         * specified capacity is larger than the current capacity.
         * @param capacity New capacity of the vector.
         */
        void reserve(size_type capacity);

        /**
         * Swaps the contents of another vector with this Vector.
         * @param other Other vector used for swapping.
         */
        friend void swap(Vector<T>& a, Vector<T>& b)
        {
            using std::swap;
            swap(a.size_, b.size_);
            swap(a.capacity_, b.capacity_);
            swap(a.data_, b.data_);
        }

        /**
         * Pushes specified value to the end of the vector.
         * @param value Value to push back.
         */
        void push_back(const_reference value);

        /**
         * Removes the last element in the vector.
         */
        void pop_back() noexcept;

        /**
         * Inserts value to the vector at specified location and shifts other values.
         * @param position Index to insert element into.
         * @param value Value to insert.
         */
        void insert(size_type position, const_reference value);

        /**
         * Inserts n amount of values to the vector at specified location and shifts other values.
         * @param position Index of the first element to insert.
         * @param n Amount of values to insert
         * @param value Value to insert.
         */
        void insert(size_type position, size_type n, const_reference value);

        /**
         * Copies values from another vector to the end of this vector.
         * @param other Vector to copy from.
         * @param start Starting index of the other vector (inclusive)
         * @param end Ending index of the other vector (exlusive)
         */
        void insert(Vector<T> const& other, size_type start, size_type end);

        /**
         * Removes all elements in the vector.
         */
        void clear() noexcept;

        reference operator[](size_type index)
        {
            if (empty() || index >= size_)
            {
                throw std::out_of_range("Index out of bounds");
            }
            iterator it = begin();
            return it[index];
        }

        const_reference operator[](size_type index) const
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
