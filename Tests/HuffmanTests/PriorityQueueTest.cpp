#include <gtest/gtest.h>
#include <common/PriorityQueue.h>

#include "common/Vector.h"

template<class T, class Compare = std::less<T>>
bool isVectorHeap(const common::Vector<T>& vectorToTest, Compare compare = Compare(), std::size_t i = 0)
{
    if (i >= (vectorToTest.size() / 2))
    {
        return true;
    }
    auto left = (i + 1) * 2 - 1;
    auto right = (i + 1) * 2;

    bool isHeap = compare(vectorToTest[left], vectorToTest[i]) && isVectorHeap(vectorToTest, compare, left);
    if (right < vectorToTest.size())
    {
        isHeap = isHeap && compare(vectorToTest[right], vectorToTest[i]) && isVectorHeap(vectorToTest, compare, right);
    }
    return isHeap;
}

TEST(PriorityQueueTest, PushBackWorksMaxQueue)
{
    common::PriorityQueue<int> queue;
    queue.push(10);
    ASSERT_TRUE(isVectorHeap(queue.data()));
    queue.push(5);
    ASSERT_TRUE(isVectorHeap(queue.data()));
    queue.push(4);
    ASSERT_TRUE(isVectorHeap(queue.data()));
    queue.push(3);
    ASSERT_TRUE(isVectorHeap(queue.data()));
    queue.push(8);
    ASSERT_TRUE(isVectorHeap(queue.data()));
}

TEST(PriorityQueueTest, PushBackWorksMinQueue)
{
    common::PriorityQueue<int, std::greater<int>> queue;
    queue.push(4);
    ASSERT_TRUE(isVectorHeap(queue.data(), std::greater<int>{}));
    queue.push(5);
    ASSERT_TRUE(isVectorHeap(queue.data(), std::greater<int>{}));
    queue.push(6);
    ASSERT_TRUE(isVectorHeap(queue.data(), std::greater<int>{}));
    queue.push(1);
    ASSERT_TRUE(isVectorHeap(queue.data(), std::greater<int>{}));
    queue.push(2);
    ASSERT_TRUE(isVectorHeap(queue.data(), std::greater<int>{}));
    queue.push(50);
    ASSERT_TRUE(isVectorHeap(queue.data(), std::greater<int>{}));
}

TEST(PriorityQueueTest, PopWorksMaxQueue)
{
    common::PriorityQueue<int> queue;

    queue.push(1);
    queue.push(2);
    queue.push(3);
    queue.push(4);
    queue.push(5);

    ASSERT_EQ(5, queue.top());

    queue.pop();
    ASSERT_EQ(4, queue.top());
    ASSERT_TRUE(isVectorHeap(queue.data()));

    queue.pop();
    ASSERT_EQ(3, queue.top());
    ASSERT_TRUE(isVectorHeap(queue.data()));

    queue.pop();
    ASSERT_EQ(2, queue.top());
    ASSERT_TRUE(isVectorHeap(queue.data()));

    queue.pop();
    ASSERT_EQ(1, queue.top());
    ASSERT_TRUE(isVectorHeap(queue.data()));
}

TEST(PriorityQueueTest, PopWorksMinQueue)
{
    common::PriorityQueue<int, std::greater<int>> queue;

    queue.push(5);
    queue.push(4);
    queue.push(3);
    queue.push(2);
    queue.push(1);

    ASSERT_EQ(1, queue.top());

    queue.pop();
    ASSERT_EQ(2, queue.top());
    ASSERT_TRUE(isVectorHeap(queue.data(), std::greater<int>{}));

    queue.pop();
    ASSERT_EQ(3, queue.top());
    ASSERT_TRUE(isVectorHeap(queue.data(), std::greater<int>{}));

    queue.pop();
    ASSERT_EQ(4, queue.top());
    ASSERT_TRUE(isVectorHeap(queue.data(), std::greater<int>{}));

    queue.pop();
    ASSERT_EQ(5, queue.top());
    ASSERT_TRUE(isVectorHeap(queue.data(), std::greater<int>{}));
}


