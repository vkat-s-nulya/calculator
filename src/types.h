#pragma once
#include <mathlib/errors.h>
#include <stdint.h>

namespace calculator
{
enum Operation
{
    UNKNOWN = -1,
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
    mathlib::Error error;
    int has_a;
    int has_b;
    int has_op;
};
}