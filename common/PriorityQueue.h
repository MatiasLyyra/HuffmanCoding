#ifndef HUFFMANCODING_PRIORITYQUEUE_H
#define HUFFMANCODING_PRIORITYQUEUE_H

#include <functional>

#include "Vector.h"

namespace common
{
    /**
     * PriorityQueue implementation using binary heap.
     * @tparam T Type of the element to store.
     * @tparam Compare Comparison function that is used to order elements.
     */
    template<class T, class Compare = std::less<T>>
    class PriorityQueue
    {
    public:
        using size_type = std::size_t;
        using iterator = T*;
        using const_iterator = T const*;
        using reference = T&;
        using const_reference = T const&;

        explicit PriorityQueue(Compare const& compare = Compare())
                : compare_{compare},
                  data_{}
        {}

        /**
         * Returns the top of the priority queue
         * @return Top of the priority queue
         */
        reference top() noexcept
        {
            return data_.front();
        }

        /**
         * Returns the top of the priority queue
         * @return Top of the priority queue
         */
        const_reference top() const noexcept
        {
            return data_.front();
        }

        /**
         * Pushes given value to the queue.
         * @param value Value to push in to the queue
         */
        void push(const_reference value)
        {
            data_.push_back(value);
            size_type index = data_.size() - 1;
            while (!is_root(index))
            {
                size_type parent_index = parent(index);
                if (compare_(data_[parent_index], data_[index]))
                {
                    swap_elements(index, parent_index);
                    index = parent_index;
                }
                else
                {
                    break;
                }
            }
        }

        /**
         * Removes the top of the queue.
         */
        void pop()
        {
            if (!data_.empty())
            {
                swap_elements(0, data_.size() - 1);
                data_.pop_back();
                heapify(0);
            }
        }

        /**
         * Provides immutable access to the underlying container.
         * @return Underlying container.
         */
        Vector<T> const& data() const noexcept
        {
            return data_;
        }

        /**
         * Returns size of the queue.
         * @return Size of the queue.
         */
        size_type size() const noexcept
        {
            return data_.size();
        }

    private:
        void heapify(size_type index)
        {
            while (has_children(index))
            {
                size_type left_index = left_child(index);
                size_type right_index = right_child(index);
                size_type smaller = left_index;
                if (right_index < data_.size())
                {
                    smaller = compare_(data_[left_index], data_[right_index]) ? right_index : left_index;
                }

                if (compare_(data_[index], data_[smaller]))
                {
                    swap_elements(smaller, index);
                    index = smaller;
                }
                else
                {
                    break;
                }
            }
        }

        bool is_root(size_type index)
        {
            return index == 0;
        }

        bool has_children(size_type index)
        {
            return data_.size() > 0 ? index < (data_.size() / 2) : false;
        }

        size_type left_child(size_type index)
        {
            return (index + 1) * 2 - 1;
        }

        size_type right_child(size_type index)
        {
            return (index + 1) * 2;
        }

        size_type parent(size_type index)
        {
            return index / 2;
        }

        void swap_elements(size_type index1, size_type index2)
        {
            T temp{data_[index1]};
            data_[index1] = data_[index2];
            data_[index2] = temp;
        }

        Compare compare_;
        Vector<T> data_;
    };
}


#endif //HUFFMANCODING_PRIORITYQUEUE_H
