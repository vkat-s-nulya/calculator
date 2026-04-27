#pragma once
#include <mathlib/errors.h>
#include <optional>
#include <stdint.h>
#include <string>

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
    int64_t a = 0;
    int64_t b = 0;
    Operation operation = Operation::ADD;
    int64_t result = 0;
    int status = 0;
};

std::string toString(Operation op);
std::optional<Operation> fromString(const std::string& s);

} // namespace calculator
