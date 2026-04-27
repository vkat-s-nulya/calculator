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
    Calculator(Calculator&&) = default;
    Calculator& operator=(Calculator&&) = default;

    void calculate(Context& ctx);
};
} // namespace calculator