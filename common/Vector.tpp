#ifndef HUFFMANCODING_VECTOR_TPP
#define HUFFMANCODING_VECTOR_TPP

template <class T>
Vector<T>::Vector(size_type size, T const& defaultValue)
        : size_(size),
          capacity_(std::max(size_, static_cast<size_type>(16))),
          data_(new char[sizeof(T) * capacity_])
{

    for (auto it = begin(); it != end() ; ++it)
    {
        new (it) T(defaultValue);
    }
}

template <class T>
Vector<T>::Vector(Vector<T> const& other)
        : size_(other.size_),
          capacity_(other.capacity_),
          data_(new char[sizeof(T) * capacity_])
{
    assert(size_ == other.size_);
    for (auto it = begin(), other_it = other.begin(); it != end(); ++it, ++other_it)
    {
        new (it) T(*other_it);
    }
}

template <class T>
Vector<T>& Vector<T>::operator=(Vector<T> other)
{
    swap(other);
    return *this;
}

template <class T>
void Vector<T>::reserve(size_type capacity)
{
    if (capacity > capacity_)
    {
        size_type new_capacity = capacity * RESERVE_MULTIPLIER;
        std::unique_ptr<char[]> tmp{new char[sizeof(T) * new_capacity]};
        iterator old_it = reinterpret_cast<iterator>(data_.get());
        iterator tmp_it = reinterpret_cast<iterator>(tmp.get());

        for (int i = 0; i < size_; ++i)
        {
            new (&tmp_it[i]) T(old_it[i]);
        }

        std::swap(capacity_, new_capacity);
        std::swap(data_, tmp);

        for (int i = 0; i < size_; ++i)
        {
            old_it[size_ - 1 - i].~T();
        }
    }
}

template <class T>
void Vector<T>::swap(Vector<T> &other) noexcept
{
    std::swap(size_, other.size_);
    std::swap(capacity_, other.capacity_);
    std::swap(data_, other.data_);
}

template <class T>
void Vector<T>::insert(size_type position, size_type n, T const& value)
{
    size_type new_size = size_ + n;
    if (position > size_)
    {
        throw std::out_of_range("Index out of bounds");
    }
    std::unique_ptr<char[]> tmp{new char[sizeof(T) * new_size]};
    size_type old_size = size_;
    auto tmp_it = reinterpret_cast<iterator>(tmp.get());
    auto old_it = begin();

    for (int i = 0; i < position; ++i)
    {
        new (&tmp_it[i]) T(old_it[i]);
    }

    for (int i = position; i < (position + n); ++i)
    {
        new (&tmp_it[i]) T(value);
    }

    for (int i = (position + n); i < new_size; ++i)
    {
        new (&tmp_it[i]) T(old_it[i]);
    }

    std::swap(size_, new_size);
    std::swap(data_, tmp);
    capacity_ = size_;

    for (int i = 0; i < old_size; ++i)
    {
        old_it[old_size - 1 - i].~T();
    }
}

template <class T>
void Vector<T>::insert(size_type position, T const& value)
{
    insert(position, 1, value);
}

template <class T>
void Vector<T>::push_back(T const &value)
{
    reserve(size_+1);
    auto it = begin();
    new (&it[size_]) T(value);
    ++size_;
}

template <class T>
void Vector<T>::pop_back() noexcept
{
    if (size_ > 0)
    {
        --size_;
        auto it = begin();
        it[size_].~T();
    }
}

template <class T>
void Vector<T>::clear() noexcept
{
    while (!empty())
    {
        pop_back();
    }
}
#endif //HUFFMANCODING_VECTOR_TPP