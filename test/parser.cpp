#include <gtest/gtest.h>
#include <stdexcept>
#include "../parser.hpp"

TEST(Parser, Simple)
{
    EXPECT_EQ(mercury::Parse("1")->Calc(), 1);
    EXPECT_EQ(mercury::Parse("2")->Calc(), 2);
    EXPECT_EQ(mercury::Parse("3")->Calc(), 3);
    EXPECT_EQ(mercury::Parse("B"), nullptr);
    EXPECT_EQ(mercury::Parse("11")->Calc(), 11);
    EXPECT_EQ(mercury::Parse("1a"), nullptr);
}

TEST(Parser, Expression)
{
    EXPECT_EQ(mercury::Parse("11+2")->Calc(), 13);
    EXPECT_EQ(mercury::Parse("0+3")->Calc(), 3);
    EXPECT_EQ(mercury::Parse("13+a"), nullptr);
    EXPECT_EQ(mercury::Parse("10+7b"), nullptr);
    EXPECT_EQ(mercury::Parse("10-7")->Calc(), 3);
    EXPECT_EQ(mercury::Parse("10*7")->Calc(), 70);
    EXPECT_EQ(mercury::Parse("6/3")->Calc(), 2);
}

TEST(Parser, Complex)
{
    //EXPECT_EQ(mercury::Parse("11 + 1 + 2 + 3"), 17);
    //EXPECT_EQ(mercury::Parse("11 * 2 / 4"), 17);
}
