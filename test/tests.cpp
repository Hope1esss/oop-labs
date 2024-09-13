#include <../include/checkBracketSequence.h>
#include <gtest/gtest.h>
#include <string>

TEST(checkBracketSequenceTest, CheckCorrectSequenceLen2) {
   std::string input_string = "()";

   bool result = checkBracketSequence(input_string);

   EXPECT_TRUE(result);
}

TEST(checkBracketSequenceTest, CheckWrongSequenceLen6) {
   std::string input_string = ")(()))";

   bool result = checkBracketSequence(input_string);

   EXPECT_FALSE(result);
}

TEST(checkBracketSequenceTest, CheckWrongSequenceLen1) {
   std::string input_string = "(";

   bool result = checkBracketSequence(input_string);

   EXPECT_FALSE(result);
}

TEST(checkBracketSequenceTest, CheckCorrectSequenceLen14) {
   std::string input_string = "(())((()())())";

   bool result = checkBracketSequence(input_string);

   EXPECT_TRUE(result);
}

TEST(checkBracketSequenceTest, CheckLongSequenceLen150) {
   std::string input_string(150, '(');

   ASSERT_THROW(checkBracketSequence(input_string),
                InvalidStringLengthException);
}

TEST(checkBracketSequenceTest, CheckEmptySequence) {
   std::string input_string = "";

   bool result = checkBracketSequence(input_string);

   EXPECT_TRUE(result);
}

TEST(checkBracketSequenceTest, CheckSequenceWithNumber) {
   std::string input_string = "7";

   ASSERT_THROW(checkBracketSequence(input_string), InvalidCharException);
}