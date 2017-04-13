#ifndef HUFFMANCODING_VECTOR_TCC
#define HUFFMANCODING_VECTOR_TCC

template <class T>
Vector<T>::Vector()
        : size_(0),
          capacity_(16),
          data_(new char[sizeof(T) * capacity_])
{
}

template <class T>
Vector<T>::Vector(iterator start, iterator end)
        : size_(end - start),
          capacity_(size_),
          data_(new char[sizeof(T) * capacity_])
{
    if (std::is_fundamental<T>::value)
    {
        auto it = begin();
        std::memcpy(it, start, sizeof(T) * (end-start));
    }
    else
    {
        auto it_input = start;
        auto it = begin();
        for (int i = 0; i < size_; ++it_input, ++i)
        {
            new (&it[i]) T(*it_input);
        }
    }

}

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
    swap(*this, other);
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

        for (auto i = 0u; i < size_; ++i)
        {
            new (&tmp_it[i]) T(old_it[i]);
        }

        std::swap(capacity_, new_capacity);
        std::swap(data_, tmp);

        for (auto i = 0u; i < size_; ++i)
        {
            old_it[size_ - 1 - i].~T();
        }
    }
}

template <class T>
void Vector<T>::insert(size_type position, size_type n, T const& value)
{
    size_type new_size = size_ + n;
    if (position > size_)
    {
        throw std::out_of_range("Index out of bounds");
    }
    Vector<T> tmp;
    tmp.reserve(new_size);
    tmp.insert(*this, 0, position);
    for (int i = 0; i < n; ++i)
    {
        tmp.push_back(T{value});
    }
    tmp.insert((*this), position, size_);

    swap(*this, tmp);
}
template <class T>
void Vector<T>::insert(Vector<T> const &other, size_type start, size_type end)
{
    if (start > end || end > other.size())
    {
        throw std::out_of_range("Invalid starting or ending indexes");
    }
    for (int i = start; i < end; ++i)
    {
        push_back(other[i]);
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
    size_type new_capacity = 16;
    std::unique_ptr<char[]> tmp{new char[sizeof(T) * new_capacity]};
    auto it = begin();
    for (int i = size_ - 1; i >= 0; --i)
    {
        it[i].~T();
    }
    size_ = 0;
    capacity_ = new_capacity;
    std::swap(data_, tmp);
}
#endif //HUFFMANCODING_VECTOR_TCC