#include "exceptions.h"
#include "parser.h"
#include <gtest/gtest.h>

using namespace calculator;

TEST(ParserTest, ParsesSimpleAddition)
{
    Parser parser;
    const Context ctx = parser.parse(R"({"a": 10, "b": 3, "op": "add"})");

    EXPECT_EQ(ctx.a, 10);
    EXPECT_EQ(ctx.b, 3);
    EXPECT_EQ(ctx.operation, Operation::ADD);
}

TEST(ParserTest, ParsesFactorialWithoutB)
{
    Parser parser;
    const Context ctx = parser.parse(R"({"a": 5, "op": "fac"})");

    EXPECT_EQ(ctx.a, 5);
    EXPECT_EQ(ctx.operation, Operation::FAC);
}

TEST(ParserTest, ParsesAllOperations)
{
    Parser parser;

    EXPECT_EQ(parser.parse(R"({"a": 1, "b": 1, "op": "add"})").operation,
              Operation::ADD);
    EXPECT_EQ(parser.parse(R"({"a": 1, "b": 1, "op": "sub"})").operation,
              Operation::SUB);
    EXPECT_EQ(parser.parse(R"({"a": 1, "b": 1, "op": "mul"})").operation,
              Operation::MUL);
    EXPECT_EQ(parser.parse(R"({"a": 1, "b": 1, "op": "div"})").operation,
              Operation::DIV);
    EXPECT_EQ(parser.parse(R"({"a": 1, "b": 1, "op": "pow"})").operation,
              Operation::POW);
    EXPECT_EQ(parser.parse(R"({"a": 1, "op": "fac"})").operation,
              Operation::FAC);
}

TEST(ParserTest, ThrowsOnInvalidJson)
{
    Parser parser;
    EXPECT_THROW(parser.parse("not json at all"), ParseError);
}

TEST(ParserTest, ThrowsOnMissingOperation)
{
    Parser parser;
    EXPECT_THROW(parser.parse(R"({"a": 1, "b": 2})"), ParseError);
}

TEST(ParserTest, ThrowsOnMissingA)
{
    Parser parser;
    EXPECT_THROW(parser.parse(R"({"b": 2, "op": "add"})"), ParseError);
}

TEST(ParserTest, ThrowsOnMissingBForNonFactorial)
{
    Parser parser;
    EXPECT_THROW(parser.parse(R"({"a": 1, "op": "add"})"), ParseError);
}

TEST(ParserTest, ThrowsOnUnknownOperation)
{
    Parser parser;
    EXPECT_THROW(parser.parse(R"({"a": 1, "b": 2, "op": "xyz"})"), ParseError);
}

TEST(ParserTest, HandlesNegativeNumbers)
{
    Parser parser;
    const Context ctx = parser.parse(R"({"a": -10, "b": -3, "op": "add"})");

    EXPECT_EQ(ctx.a, -10);
    EXPECT_EQ(ctx.b, -3);
}
