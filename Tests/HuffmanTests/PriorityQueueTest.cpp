#include <gtest/gtest.h>
#include <common/PriorityQueue.h>

#include "common/Vector.h"

template <class T, class Compare = std::less<T>>
bool isVectorHeap(const common::Vector<T>& vectorToTest, Compare compare = Compare(), std::size_t i = 0)
{
    if (i >= (vectorToTest.size() / 2))
    {
        return true;
    }
    auto left = (i + 1) * 2 - 1;
    auto right = (i + 1) * 2;

    bool isHeap = compare(vectorToTest[i], vectorToTest[left]) && isVectorHeap(vectorToTest, compare, left);
    if (right < vectorToTest.size())
    {
        isHeap = isHeap && compare(vectorToTest[i], vectorToTest[right]) && isVectorHeap(vectorToTest, compare, right);
    }
    return isHeap;
}

TEST(PriorityQueueTest, PushBackWorksMinQueue)
{
    common::PriorityQueue<int> queue;
    queue.push_back(10);
    ASSERT_TRUE(isVectorHeap(queue.data()));
    queue.push_back(5);
    ASSERT_TRUE(isVectorHeap(queue.data()));
    queue.push_back(4);
    ASSERT_TRUE(isVectorHeap(queue.data()));
    queue.push_back(3);
    ASSERT_TRUE(isVectorHeap(queue.data()));
    queue.push_back(8);
    ASSERT_TRUE(isVectorHeap(queue.data()));
}

TEST(PriorityQueueTest, PushBackWorksMaxQueue)
{
    common::PriorityQueue<int, std::greater<int>> queue;
    queue.push_back(4);
    ASSERT_TRUE(isVectorHeap(queue.data(), std::greater<int>{}));
    queue.push_back(5);
    ASSERT_TRUE(isVectorHeap(queue.data(), std::greater<int>{}));
    queue.push_back(6);
    ASSERT_TRUE(isVectorHeap(queue.data(), std::greater<int>{}));
    queue.push_back(1);
    ASSERT_TRUE(isVectorHeap(queue.data(), std::greater<int>{}));
    queue.push_back(2);
    ASSERT_TRUE(isVectorHeap(queue.data(), std::greater<int>{}));
    queue.push_back(50);
    ASSERT_TRUE(isVectorHeap(queue.data(), std::greater<int>{}));
}

TEST(PriorityQueueTest, PopWorksMinQueue)
{
    common::PriorityQueue<int> queue;
    queue.push_back(5);
    queue.push_back(4);
    queue.push_back(3);
    queue.push_back(2);
    queue.push_back(1);

    ASSERT_EQ(1, queue.top());

    queue.pop();
    ASSERT_EQ(2, queue.top());
    ASSERT_TRUE(isVectorHeap(queue.data()));

    queue.pop();
    ASSERT_EQ(3, queue.top());
    ASSERT_TRUE(isVectorHeap(queue.data()));

    queue.pop();
    ASSERT_EQ(4, queue.top());
    ASSERT_TRUE(isVectorHeap(queue.data()));

    queue.pop();
    ASSERT_EQ(5, queue.top());
    ASSERT_TRUE(isVectorHeap(queue.data()));
}

TEST(PriorityQueueTest, PopWorksMaxQueue)
{
    common::PriorityQueue<int, std::greater<int>> queue;
    queue.push_back(1);
    queue.push_back(2);
    queue.push_back(3);
    queue.push_back(4);
    queue.push_back(5);

    ASSERT_EQ(5, queue.top());

    queue.pop();
    ASSERT_EQ(4, queue.top());
    ASSERT_TRUE(isVectorHeap(queue.data(), std::greater<int>{}));

    queue.pop();
    ASSERT_EQ(3, queue.top());
    ASSERT_TRUE(isVectorHeap(queue.data(), std::greater<int>{}));

    queue.pop();
    ASSERT_EQ(2, queue.top());
    ASSERT_TRUE(isVectorHeap(queue.data(), std::greater<int>{}));

    queue.pop();
    ASSERT_EQ(1, queue.top());
    ASSERT_TRUE(isVectorHeap(queue.data(), std::greater<int>{}));
}


