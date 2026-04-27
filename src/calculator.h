#pragma once
#include "types.h"

namespace calculator
{
class Calculator
{
public:
    Calculator() = default;
    ~Calculator() = default;

    Calculator(const Calculator&) = default;
    Calculator& operator=(const Calculator&) = default;
    Calculator(Calculator&&) noexcept = default;
    Calculator& operator=(Calculator&&) noexcept = default;

    void calculate(Context& ctx);
};
} // namespace calculator