#pragma once
#include <mathlib/errors.h>
#include <stdint.h>

namespace calculator
{
enum class Operation
{
    ADD = 0,
    SUB = 1,
    MUL = 2,
    DIV = 3,
    POW = 4,
    FAC = 5
};

struct Context
{
    int64_t a;
    int64_t b;
    Operation operation;
    int64_t result;
};
}