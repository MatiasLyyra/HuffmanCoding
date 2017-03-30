#include <gtest/gtest.h>
#include <common/Vector.h>
#include <huffman/TreeNode.h>

class VectorFixture : public ::testing::Test
{
public:
    VectorFixture()
            : intVector{4, 5},
              initiallyEmpty{},
              treeNodeVector{}
    {
    }
protected:
    virtual void TearDown()
    {

    }

    virtual void SetUp()
    {

    }
    common::Vector<int> intVector;
    common::Vector<int> initiallyEmpty;
    common::Vector<huffman::TreeNode> treeNodeVector;
};


TEST_F(VectorFixture, ConstructorWorks)
{
    common::Vector<huffman::TreeNode> vector{4, huffman::TreeNode{0}};
    ASSERT_EQ(4, vector.size());
    huffman::TreeNode treeNode{0};
    for (auto it = vector.begin(); it != vector.end() ; ++it)
    {
        ASSERT_EQ(treeNode.getHandle(), it->getHandle());
        ASSERT_EQ(treeNode.getData(), it->getData());
        ASSERT_EQ(treeNode.getRightChildHandle(), it->getRightChildHandle());
        ASSERT_EQ(treeNode.getLeftChildHandle(), it->getLeftChildHandle());
        ASSERT_EQ(treeNode.getFrequency(), it->getFrequency());
        ASSERT_EQ(treeNode.isLeaf(), it->isLeaf());
    }
    ASSERT_EQ(4, intVector.size());
    ASSERT_EQ(0, initiallyEmpty.size());
    ASSERT_EQ(0, treeNodeVector.size());
    ASSERT_TRUE(treeNodeVector.empty());
    ASSERT_TRUE(initiallyEmpty.empty());
    ASSERT_FALSE(intVector.empty());
}

TEST_F(VectorFixture, PushAndPopkWorks)
{
    initiallyEmpty.push_back(1);
    initiallyEmpty.push_back(2);
    initiallyEmpty.push_back(5);
    initiallyEmpty.pop_back();
    initiallyEmpty.push_back(3);
    ASSERT_EQ(1, initiallyEmpty[0]);
    ASSERT_EQ(2, initiallyEmpty[1]);
    ASSERT_EQ(3, initiallyEmpty[2]);
    ASSERT_EQ(3, initiallyEmpty.size());
    ASSERT_FALSE(initiallyEmpty.empty());
}

TEST_F(VectorFixture, CopyConstructorWorks)
{
    common::Vector<int> vector{intVector};
    ASSERT_EQ(intVector.size(), vector.size());
    ASSERT_EQ(intVector.capacity(), vector.capacity());
    for (auto expected = intVector.begin(), actual = vector.begin();
         expected != intVector.end(); ++expected, ++actual)
    {
        ASSERT_EQ(*expected, *actual);
    }

    intVector.push_back(5);
    vector = intVector;

    ASSERT_EQ(intVector.size(), vector.size());
    ASSERT_EQ(intVector.capacity(), vector.capacity());
    for (auto expected = intVector.begin(), actual = vector.begin();
         expected != intVector.end(); ++expected, ++actual)
    {
        ASSERT_EQ(*expected, *actual);
    }
}

TEST_F(VectorFixture, VectorWorksWithReserve)
{
    int expected[5000];
    for (int i = 0; i < 5000; ++i)
    {
        expected[i] = i;
        initiallyEmpty.push_back(i);
    }
    ASSERT_EQ(5000, initiallyEmpty.size());
    for (int i = 0; i < 5000; ++i)
    {
        ASSERT_EQ(expected[i], initiallyEmpty[i]);
    }
    common::Vector<int> vector;
    vector.reserve(5000);
    ASSERT_TRUE(5000 <= vector.capacity());
}

TEST_F(VectorFixture, InsertWorks)
{
    int expected[8] = {1, 5, 5, 6, 6, 6, 5, 5};
    intVector.insert(0, 1);
    intVector.insert(3, 3, 6);

    ASSERT_EQ(8, intVector.size());
    for (int i = 0; i < 8; ++i)
    {
        ASSERT_EQ(expected[i], intVector[i]);
    }
}


TEST_F(VectorFixture, ExceptionsAreThrown)
{
    EXPECT_THROW(initiallyEmpty[0], std::out_of_range);
    EXPECT_THROW(initiallyEmpty[-1], std::out_of_range);
    EXPECT_THROW(initiallyEmpty[1], std::out_of_range);

    EXPECT_THROW(initiallyEmpty.front(), std::out_of_range);
    EXPECT_THROW(initiallyEmpty.back(), std::out_of_range);

    EXPECT_THROW(initiallyEmpty.at(0), std::out_of_range);
    EXPECT_THROW(initiallyEmpty.at(-1), std::out_of_range);
    EXPECT_THROW(initiallyEmpty.at(1), std::out_of_range);

    const auto constVector = initiallyEmpty;
    EXPECT_THROW(constVector[0], std::out_of_range);
    EXPECT_THROW(constVector[-1], std::out_of_range);
    EXPECT_THROW(constVector[1], std::out_of_range);

    EXPECT_THROW(constVector.front(), std::out_of_range);
    EXPECT_THROW(constVector.back(), std::out_of_range);

    EXPECT_THROW(constVector.at(0), std::out_of_range);
    EXPECT_THROW(constVector.at(-1), std::out_of_range);
    EXPECT_THROW(constVector.at(1), std::out_of_range);
}

TEST_F(VectorFixture, SubscriptOperatorAndAtWorks)
{
    initiallyEmpty.push_back(3);
    initiallyEmpty.push_back(2);
    initiallyEmpty.push_back(1);

    ASSERT_EQ(1, initiallyEmpty.at(2));
    ASSERT_EQ(2, initiallyEmpty.at(1));
    ASSERT_EQ(3, initiallyEmpty.at(0));

    ASSERT_EQ(1, initiallyEmpty[2]);
    ASSERT_EQ(2, initiallyEmpty[1]);
    ASSERT_EQ(3, initiallyEmpty[0]);

    initiallyEmpty.at(0) = 4;
    initiallyEmpty[1] = 5;
    ASSERT_EQ(4, initiallyEmpty[0]);
    ASSERT_EQ(5, initiallyEmpty[1]);

    const auto constVector = initiallyEmpty;
    ASSERT_EQ(1, constVector.at(2));
    ASSERT_EQ(5, constVector.at(1));
    ASSERT_EQ(4, constVector.at(0));

    ASSERT_EQ(1, constVector[2]);
    ASSERT_EQ(5, constVector[1]);
    ASSERT_EQ(4, constVector[0]);
}

TEST_F(VectorFixture, FrontAndBack)
{
    initiallyEmpty.push_back(1);

    ASSERT_EQ(1, initiallyEmpty.front());
    ASSERT_EQ(1, initiallyEmpty.back());

    initiallyEmpty.push_back(2);
    initiallyEmpty.push_back(3);

    ASSERT_EQ(1, initiallyEmpty.front());
    ASSERT_EQ(3, initiallyEmpty.back());

    initiallyEmpty.clear();
    initiallyEmpty.push_back(1);
    const auto constVector = initiallyEmpty;
    ASSERT_EQ(1, constVector.front());
    ASSERT_EQ(1, constVector.back());

    initiallyEmpty.push_back(2);
    initiallyEmpty.push_back(3);
    const auto constVector2 = initiallyEmpty;
    ASSERT_EQ(1, constVector2.front());
    ASSERT_EQ(3, constVector2.back());
}

TEST_F(VectorFixture, ClearingVectorWorks)
{
    initiallyEmpty.push_back(1);
    initiallyEmpty.push_back(1);
    initiallyEmpty.push_back(1);
    initiallyEmpty.push_back(1);
    initiallyEmpty.clear();

    ASSERT_TRUE(initiallyEmpty.empty());
    ASSERT_EQ(0, initiallyEmpty.size());
}