#include "calculator.h"
#include "exceptions.h"
#include <cstdint>
#include <gtest/gtest.h>
#include <limits>

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

TEST(CalculatorTest, Addition)
{
    Calculator calc;
    Context ctx = makeCtx(10, 3, Operation::ADD);
    calc.calculate(ctx);
    EXPECT_EQ(ctx.result, 13);
}

TEST(CalculatorTest, Subtraction)
{
    Calculator calc;
    Context ctx = makeCtx(10, 3, Operation::SUB);
    calc.calculate(ctx);
    EXPECT_EQ(ctx.result, 7);
}

TEST(CalculatorTest, Multiplication)
{
    Calculator calc;
    Context ctx = makeCtx(10, 3, Operation::MUL);
    calc.calculate(ctx);
    EXPECT_EQ(ctx.result, 30);
}

TEST(CalculatorTest, Division)
{
    Calculator calc;
    Context ctx = makeCtx(10, 3, Operation::DIV);
    calc.calculate(ctx);
    EXPECT_EQ(ctx.result, 3);
}

TEST(CalculatorTest, Power)
{
    Calculator calc;
    Context ctx = makeCtx(2, 10, Operation::POW);
    calc.calculate(ctx);
    EXPECT_EQ(ctx.result, 1024);
}

TEST(CalculatorTest, Factorial)
{
    Calculator calc;
    Context ctx = makeCtx(5, 0, Operation::FAC);
    calc.calculate(ctx);
    EXPECT_EQ(ctx.result, 120);
}

TEST(CalculatorTest, OverflowOnLargeMultiplication)
{
    Calculator calc;
    Context ctx =
        makeCtx(std::numeric_limits<int64_t>::max(), 2, Operation::MUL);
    EXPECT_THROW(calc.calculate(ctx), CalculationError);
}

TEST(CalculatorTest, OverflowOnLargeFactorial)
{
    Calculator calc;
    Context ctx = makeCtx(100, 0, Operation::FAC);
    EXPECT_THROW(calc.calculate(ctx), CalculationError);
}
