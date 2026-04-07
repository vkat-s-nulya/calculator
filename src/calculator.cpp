#include "calculator.h"
#include <mathlib/mathlib.h>

void calculator::calculate(Context *ctx)
{
    switch (ctx->operation)
    {
    case Operation::ADD:
        ctx->error = mathlib::add(ctx->a, ctx->b, &ctx->result);
        break;
    case Operation::SUB:
        ctx->error = mathlib::sub(ctx->a, ctx->b, &ctx->result);
        break;
    case Operation::MUL:
        ctx->error = mathlib::mul(ctx->a, ctx->b, &ctx->result);
        break;
    case Operation::DIV:
        ctx->error = mathlib::div(ctx->a, ctx->b, &ctx->result);
        break;
    case Operation::POW:
        ctx->error = mathlib::pow(ctx->a, ctx->b, &ctx->result);
        break;
    case Operation::FAC:
        ctx->error = mathlib::fac(ctx->a, &ctx->result);
        break;
    case Operation::UNKNOWN:
        ctx->error = mathlib::Error::UNSUPPORTED_OPERATION;
        break;
    default:
        break;
    }
}