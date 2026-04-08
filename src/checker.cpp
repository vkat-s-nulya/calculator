#include "checker.h"

void calculator::check(Context* ctx)
{
    if (ctx->operation == Operation::UNKNOWN)
    {
        ctx->error = mathlib::INVALID_ARGUMENT;
        return;
    }
    if (ctx->operation == Operation::DIV && ctx->b == 0)
    {
        ctx->error = mathlib::DIVISION_BY_ZERO;
        return;
    }
    if (ctx->operation == Operation::POW && ctx->b < 0)
    {
        ctx->error = mathlib::INVALID_ARGUMENT;
        return;
    }
    if (ctx->operation == Operation::FAC && ctx->a < 0)
    {
        ctx->error = mathlib::INVALID_ARGUMENT;
        return;
    }
}
