#include <gtest/gtest.h>
#include "../parser.hpp"

TEST(Parser, Simple)
{
    EXPECT_TRUE(mercury::Parse("1"));
    EXPECT_TRUE(mercury::Parse("2"));
    EXPECT_TRUE(mercury::Parse("3"));
    EXPECT_FALSE(mercury::Parse("B"));
    EXPECT_TRUE(mercury::Parse("11"));
    EXPECT_FALSE(mercury::Parse("1a"));
}

TEST(Parser, Expression)
{
    EXPECT_TRUE(mercury::Parse("11+2"));
    EXPECT_TRUE(mercury::Parse("0+3"));
    EXPECT_FALSE(mercury::Parse("13+a"));
    EXPECT_FALSE(mercury::Parse("10+7b"));
}
