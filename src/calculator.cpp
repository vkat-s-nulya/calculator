#include "calculator.h"
#include "exceptions.h"
#include "logger.h"
#include <mathlib/mathlib.h>

namespace calculator
{
void Calculator::calculate(Context& ctx)
{
    Logger::instance().debug("calculating");

    mathlib::Error err = mathlib::OK;

    switch (ctx.operation)
    {
    case Operation::ADD:
        err = mathlib::add(ctx.a, ctx.b, &ctx.result);
        break;
    case Operation::SUB:
        err = mathlib::sub(ctx.a, ctx.b, &ctx.result);
        break;
    case Operation::MUL:
        err = mathlib::mul(ctx.a, ctx.b, &ctx.result);
        break;
    case Operation::DIV:
        err = mathlib::div(ctx.a, ctx.b, &ctx.result);
        break;
    case Operation::POW:
        err = mathlib::pow(ctx.a, ctx.b, &ctx.result);
        break;
    case Operation::FAC:
        err = mathlib::fac(ctx.a, &ctx.result);
        break;
    }

    switch (err)
    {
    case mathlib::OK:
        return;
    case mathlib::OVERFLOW:
        throw CalculationError("overflow");
    case mathlib::DIVISION_BY_ZERO:
        throw CalculationError("division by zero");
    case mathlib::INVALID_ARGUMENT:
        throw CalculationError("invalid argument");
    default:
        throw CalculationError("unknown calculation error");
    }
}
}
