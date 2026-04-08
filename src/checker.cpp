#include "checker.h"
#include <stdio.h>

void calculator::check(Context* ctx)
{
    if (!ctx->has_op)
    {
        printf("Error: operation is required (-o)\n");
        ctx->error = mathlib::INVALID_ARGUMENT;
        return;
    }
    if (ctx->operation == Operation::UNKNOWN)
    {
        printf("Error: unknown operation\n");
        ctx->error = mathlib::INVALID_ARGUMENT;
        return;
    }
    if (!ctx->has_a)
    {
        printf("Error: first number is required (-a)\n");
        ctx->error = mathlib::INVALID_ARGUMENT;
        return;
    }
    if (ctx->operation != Operation::FAC && !ctx->has_b)
    {
        printf("Error: second number is required (-b)\n");
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
