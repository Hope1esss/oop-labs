#include "../include/Eleven.h"
#include <gtest/gtest.h>

TEST(ElevenTest, DefaultConstructorTest)
{
    Eleven number;

    size_t expectedSize = 0;
    unsigned char *expectedData = nullptr;

    size_t realSize = number.getSize();
    unsigned char *realData = number.getData();

    ASSERT_TRUE(expectedSize == realSize);
    ASSERT_TRUE(expectedData == realData);
}

TEST(ElevenTest, LengthAndValueConstructorTest)
{
    size_t length = 4;
    unsigned char value = '5';

    size_t expectedSize = 4;
    unsigned char expectedData[] = {'5', '5', '5', '5'};

    Eleven number(length, value);
    size_t realSize = number.getSize();
    unsigned char *realData = number.getData();

    ASSERT_TRUE(expectedSize == realSize);
    ASSERT_TRUE(expectedData[0] == realData[0]);
    ASSERT_TRUE(expectedData[1] == realData[1]);
    ASSERT_TRUE(expectedData[2] == realData[2]);
    ASSERT_TRUE(expectedData[3] == realData[3]);
}

TEST(ElevenTest, ListConstructorTest)
{
    std::initializer_list<unsigned char> list = {'1', '2', '3'};

    size_t expectedSize = 3;
    unsigned char expectedData[] = {'1', '2', '3'};

    Eleven number(list);

    size_t realSize = number.getSize();
    unsigned char *realData = number.getData();

    ASSERT_TRUE(expectedSize == realSize);
    ASSERT_TRUE(expectedData[0] == realData[0]);
    ASSERT_TRUE(expectedData[1] == realData[1]);
    ASSERT_TRUE(expectedData[2] == realData[2]);
}

TEST(ElevenTest, StringConstructorTest)
{
    std::string str = "123A2";
    size_t expectedSize = 5;
    unsigned char expectedData[] = {'1', '2', '3', 'A', '2'};

    Eleven number(str);
    size_t realSize = number.getSize();
    unsigned char *realData = number.getData();

    ASSERT_TRUE(expectedSize == realSize);
    ASSERT_TRUE(expectedData[0] == realData[0]);
    ASSERT_TRUE(expectedData[1] == realData[1]);
    ASSERT_TRUE(expectedData[2] == realData[2]);
    ASSERT_TRUE(expectedData[3] == realData[3]);
    ASSERT_TRUE(expectedData[4] == realData[4]);
}

TEST(ElevenTest, CopyConstructorTest)
{

    std::string str = "123";
    size_t expectedSize = 3;
    unsigned char expectedData[] = {'1', '2', '3'};

    Eleven number1(str);
    Eleven number2(number1);
    size_t realSize = number2.getSize();
    unsigned char *realData = number2.getData();

    ASSERT_TRUE(expectedSize == realSize);
    ASSERT_TRUE(expectedData[0] == realData[0]);
    ASSERT_TRUE(expectedData[1] == realData[1]);
    ASSERT_TRUE(expectedData[2] == realData[2]);
}

TEST(ElevenTest, MoveConstructorTest)
{

    std::string str = "123";
    size_t expectedSize = 3;
    unsigned char expectedData[] = {'1', '2', '3'};

    Eleven number1(str);
    Eleven number2(std::move(number1));
    size_t realSize = number2.getSize();
    unsigned char *realData = number2.getData();

    ASSERT_TRUE(expectedSize == realSize);
    ASSERT_TRUE(expectedData[0] == realData[0]);
    ASSERT_TRUE(expectedData[1] == realData[1]);
    ASSERT_TRUE(expectedData[2] == realData[2]);
}

TEST(ElevenTest, AssignmentTest)
{
    std::string str = "123";
    size_t expectedSize = 3;
    unsigned char expectedData[] = {'1', '2', '3'};

    Eleven number1(str);
    Eleven number2;
    number2 = number1;
    size_t realSize = number2.getSize();
    unsigned char *realData = number2.getData();

    ASSERT_TRUE(expectedSize == realSize);
    ASSERT_TRUE(expectedData[0] == realData[0]);
    ASSERT_TRUE(expectedData[1] == realData[1]);
    ASSERT_TRUE(expectedData[2] == realData[2]);
}

TEST(ElevenTest, AddUpTest)
{

    std::string str = "123";
    std::string str2 = "A42";
    size_t expectedSize = 3;
    unsigned char expectedData[] = {'0', '7', '5'};

    Eleven number1(str);
    Eleven number2(str2);
    number2 += number1;
    size_t realSize = number2.getSize();
    unsigned char *realData = number2.getData();

    ASSERT_TRUE(expectedSize == realSize);
    ASSERT_TRUE(expectedData[0] == realData[0]);
    ASSERT_TRUE(expectedData[1] == realData[1]);
    ASSERT_TRUE(expectedData[2] == realData[2]);
    ASSERT_TRUE(expectedData[3] == realData[3]);
}

TEST(ElevenTest, SubstractTest)
{
    std::string str = "123";
    std::string str2 = "A42";
    size_t expectedSize = 2;
    unsigned char expectedData[] = {'2', '8'};

    Eleven subResult(str);
    Eleven number2(str2);
    subResult -= number2;
    size_t realSize = subResult.getSize();
    unsigned char *realData = subResult.getData();

    ASSERT_TRUE(expectedSize == realSize);
    ASSERT_TRUE(expectedData[0] == realData[0]);
    ASSERT_TRUE(expectedData[1] == realData[1]);
}

TEST(ElevenTest, CompareLessTest)
{

    std::string str = "123";
    std::string str2 = "A42";
    Eleven number1(str);
    Eleven number2(str2);

    bool result = number2 < number1;

    ASSERT_TRUE(result);
}

TEST(ElevenTest, CompareGreatTest)
{

    std::string str = "123";
    std::string str2 = "A42";
    Eleven number1(str);
    Eleven number2(str2);

    bool result = number1 > number2;

    ASSERT_TRUE(result);
}

TEST(ElevenTest, CompareEqualTest)
{

    std::string str = "123";
    std::string str2 = "123";

    Eleven number1(str);
    Eleven number2(str2);

    bool result = number1 == number2;

    ASSERT_TRUE(result);
}