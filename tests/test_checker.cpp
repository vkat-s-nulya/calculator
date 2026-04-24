#include "checker.h"
#include "exceptions.h"
#include <gtest/gtest.h>

using namespace calculator;

static Context makeCtx(int64_t a, int64_t b, Operation op)
{
    Context ctx;
    ctx.a = a;
    ctx.b = b;
    ctx.operation = op;
    ctx.result = 0;
    return ctx;
}

TEST(CheckerTest, ValidAdditionPasses)
{
    Checker checker;
    EXPECT_NO_THROW(checker.check(makeCtx(1, 2, Operation::ADD)));
}

TEST(CheckerTest, DivisionByZeroThrows)
{
    Checker checker;
    EXPECT_THROW(checker.check(makeCtx(10, 0, Operation::DIV)), ValidationError);
}

TEST(CheckerTest, DivisionByNonZeroPasses)
{
    Checker checker;
    EXPECT_NO_THROW(checker.check(makeCtx(10, 2, Operation::DIV)));
}

TEST(CheckerTest, NegativeExponentThrows)
{
    Checker checker;
    EXPECT_THROW(checker.check(makeCtx(2, -3, Operation::POW)), ValidationError);
}

TEST(CheckerTest, PositiveExponentPasses)
{
    Checker checker;
    EXPECT_NO_THROW(checker.check(makeCtx(2, 3, Operation::POW)));
}

TEST(CheckerTest, NegativeFactorialThrows)
{
    Checker checker;
    EXPECT_THROW(checker.check(makeCtx(-5, 0, Operation::FAC)), ValidationError);
}

TEST(CheckerTest, NonNegativeFactorialPasses)
{
    Checker checker;
    EXPECT_NO_THROW(checker.check(makeCtx(5, 0, Operation::FAC)));
}
