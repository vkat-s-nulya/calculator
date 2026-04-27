#pragma once
#include "types.h"

namespace calculator
{
class Checker
{
public:
    Checker() = default;
    ~Checker() = default;

    Checker(const Checker&) = default;
    Checker& operator=(const Checker&) = default;
    Checker(Checker&&) = default;
    Checker& operator=(Checker&&) = default;

    void check(const Context& ctx);
};
} // namespace calculator