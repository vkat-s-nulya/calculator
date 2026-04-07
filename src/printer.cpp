#include "printer.h"
#include <inttypes.h>
#include <stdio.h>

void calculator::print(Context *ctx)
{
    if (ctx->error == mathlib::Error::OK)
    {
        printf("Result: %" PRId64 "\n", ctx->result);
        return;
    }

    switch (ctx->error)
    {
    case mathlib::Error::OVERFLOW:
        printf("Error: overflow\n");
        break;
    case mathlib::Error::INVALID_ARGUMENT:
        printf("Error: invalid argument\n");
        break;
    case mathlib::Error::DIVISION_BY_ZERO:
        printf("Error: division by zero\n");
        break;
    case mathlib::Error::UNSUPPORTED_OPERATION:
        printf("Error: operation not supported\n");
        break;
    default:
        printf("Error: unknown error\n");
        break;
    }
}