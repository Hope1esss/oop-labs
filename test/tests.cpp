#include <gtest/gtest.h>
#include "../src/MyMemoryResource.cpp"
#include "../src/SinglyLinkedList.cpp"
#include <memory>

TEST(SinglyLinkedListTest, PushTest)
{
    MyMemoryResource memoryResource(SinglyLinkedList<int>::getNodeSize() * 4);
    SinglyLinkedList<int> intList(&memoryResource);

    intList.push_front(1);
    intList.push_front(2);
    intList.push_front(4);
    intList.push_front(8);

    auto it = intList.begin();
    EXPECT_EQ(*it, 8);
    ++it;
    EXPECT_EQ(*it, 4);
    ++it;
    EXPECT_EQ(*it, 2);
    ++it;
    EXPECT_EQ(*it, 1);
}

TEST(SinglyLinkedListTest, PopTest)
{
    MyMemoryResource memoryResource(SinglyLinkedList<int>::getNodeSize() * 4);
    SinglyLinkedList<int> intList(&memoryResource);

    intList.push_front(1);
    intList.push_front(2);
    intList.push_front(4);
    intList.push_front(8);

    intList.pop_front();
    auto it = intList.begin();
    EXPECT_EQ(*it, 4);
    intList.pop_front();
}

TEST(SinglyLinkedListTest, PushComplexTypeTest)
{
    struct ComplexType
    {
        int id;
        std::string name;
    };

    MyMemoryResource memoryResource(SinglyLinkedList<ComplexType>::getNodeSize() * 3);
    SinglyLinkedList<ComplexType> complexList(&memoryResource);

    complexList.push_front({1, "Ann"});
    complexList.push_front({2, "Oleg"});
    complexList.push_front({3, "Vanya"});

    auto it = complexList.begin();
    EXPECT_EQ(it->id, 3);
    EXPECT_EQ(it->name, "Vanya");
    ++it;
    EXPECT_EQ(it->id, 2);
    EXPECT_EQ(it->name, "Oleg");
    ++it;
    EXPECT_EQ(it->id, 1);
    EXPECT_EQ(it->name, "Ann");
}

TEST(SinglyLinkedListTest, OperationsTest)
{
    MyMemoryResource memoryResource(SinglyLinkedList<int>::getNodeSize() * 3);
    SinglyLinkedList<int> intList(&memoryResource);

    intList.push_front(2);
    intList.pop_front();
    intList.push_front(5);
    intList.push_front(1);
    intList.pop_front();
    intList.pop_front();

    EXPECT_EQ(intList.begin(), intList.end());
}

TEST(SinglyLinkedListTest, IteratorEqualTest)
{
    MyMemoryResource memoryResource(SinglyLinkedList<int>::getNodeSize() * 3);
    SinglyLinkedList<int> intList(&memoryResource);

    intList.push_front(2);
    intList.push_front(2);

    auto it1 = intList.begin();
    auto it2 = intList.begin();
    EXPECT_TRUE(it1 == it2);
}

TEST(SinglyLinkedList, IteratorNotEqualTest)
{
    MyMemoryResource memoryResource(SinglyLinkedList<int>::getNodeSize() * 3);
    SinglyLinkedList<int> intList(&memoryResource);

    auto it1 = intList.begin();
    
    intList.push_front(1);

    auto it2 = intList.begin();
    EXPECT_TRUE(it1 != it2);
}