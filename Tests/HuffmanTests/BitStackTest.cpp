#include <gtest/gtest.h>
#include <common/BitStack.h>

class BitStackFixture :
        public ::testing::Test
{
public:
    BitStackFixture()
            : initiallyEmpty{},
              stackWithValues{}
    {

    }

    virtual void TearDown()
    {

    }

    virtual void SetUp()
    {
        stackWithValues.push_back(false);
        stackWithValues.push_back(true);
        stackWithValues.push_back(true);
        stackWithValues.push_back(5, 3);
    }

    common::BitStack initiallyEmpty;
    common::BitStack stackWithValues;
};

TEST_F(BitStackFixture, InitialValuesAreCorrect)
{
    ASSERT_EQ(0, initiallyEmpty.size());
    ASSERT_TRUE(0 < initiallyEmpty.capacity());

    ASSERT_EQ(6, stackWithValues.size());
    ASSERT_TRUE(0 < stackWithValues.capacity());

    bool expectedValues[6] = {false, true, true, true, false, true};
    for (int i = 0; i < 6; ++i)
    {
        ASSERT_EQ(expectedValues[i], stackWithValues[i]);
    }
}

TEST_F(BitStackFixture, PushingBackMultipleValuesWorks)
{
    initiallyEmpty.push_back(0xFFFFFFFF, 32);
    initiallyEmpty.push_back(0xFFFFFFFF, 32);
    initiallyEmpty.push_back(0xFFFFFFFF, 32);
    initiallyEmpty.push_back(0xFFFFFFFF, 32);
    initiallyEmpty.push_back(0xFFFFFFFF, 32);
    initiallyEmpty.push_back(0xFFFFFFFF, 32);

    initiallyEmpty.push_back(0, 32);
    initiallyEmpty.push_back(0, 32);
    initiallyEmpty.push_back(0, 32);
    initiallyEmpty.push_back(0, 32);
    initiallyEmpty.push_back(0, 32);
    initiallyEmpty.push_back(0, 32);

    initiallyEmpty.push_back(0xFFFFFFFF, 10);
    initiallyEmpty.push_back(0, 24);
    initiallyEmpty.push_back(0xFFFFFFFF, 32);


    for (int i = 0; i < 192; ++i)
    {
        ASSERT_TRUE(initiallyEmpty[i]);
        ASSERT_TRUE(initiallyEmpty.at(i));
    }

    for (int i = 192; i < 384; ++i)
    {
        ASSERT_FALSE(initiallyEmpty[i]);
        ASSERT_FALSE(initiallyEmpty.at(i));
    }

    for (int i = 384; i < 394; ++i)
    {
        ASSERT_TRUE(initiallyEmpty[i]);
        ASSERT_TRUE(initiallyEmpty.at(i));
    }

    for (int i = 394; i < 418; ++i)
    {
        ASSERT_FALSE(initiallyEmpty[i]);
        ASSERT_FALSE(initiallyEmpty.at(i));
    }

    for (int i = 418; i < 450; ++i)
    {
        ASSERT_TRUE(initiallyEmpty[i]);
        ASSERT_TRUE(initiallyEmpty.at(i));
    }

    ASSERT_EQ(450, initiallyEmpty.size());
}

TEST_F(BitStackFixture, ClearingWorks)
{
    stackWithValues.clear();
    ASSERT_EQ(0, stackWithValues.size());
}

TEST_F(BitStackFixture, ExceptionsAreThrown)
{
    ASSERT_THROW(initiallyEmpty[0], std::invalid_argument);
    ASSERT_THROW(initiallyEmpty.at(0), std::invalid_argument);

    ASSERT_THROW(initiallyEmpty[-1], std::invalid_argument);
    ASSERT_THROW(initiallyEmpty.at(-1), std::invalid_argument);

    ASSERT_THROW(initiallyEmpty[1], std::invalid_argument);
    ASSERT_THROW(initiallyEmpty.at(1), std::invalid_argument);

    initiallyEmpty.push_back(true);
    initiallyEmpty.push_back(true);

    ASSERT_THROW(initiallyEmpty[2], std::invalid_argument);
    ASSERT_THROW(initiallyEmpty.at(2), std::invalid_argument);

    ASSERT_THROW(initiallyEmpty.push_back(4, 33), std::invalid_argument);
}

TEST_F(BitStackFixture, ClearingValuesWorks)
{
    bool expectedValues[8] = {false, false, false, false, true, true, true, true};
    initiallyEmpty.push_back(false);
    initiallyEmpty.push_back(false);
    initiallyEmpty.push_back(false);
    initiallyEmpty.push_back(false);
    initiallyEmpty.push_back(0xFF, 4);

    for (int i = 0; i < 8; ++i)
    {
        ASSERT_EQ(expectedValues[i], initiallyEmpty[i]);
    }
}

TEST_F(BitStackFixture, PopBackWorks)
{
    initiallyEmpty.pop_back();
    ASSERT_EQ(0, initiallyEmpty.size());

    initiallyEmpty.push_back(true);
}

TEST_F(BitStackFixture, ReserveWorks)
{
    initiallyEmpty.reserve(500);
    ASSERT_TRUE(500 <= initiallyEmpty.capacity());
}

TEST_F(BitStackFixture, TopWorks)
{
    ASSERT_EQ(true, stackWithValues.top());
    stackWithValues.pop_back();
    ASSERT_EQ(false, stackWithValues.top());
    stackWithValues.pop_back();
    ASSERT_EQ(true, stackWithValues.top());
}