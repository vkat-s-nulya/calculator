#pragma once
#include "types.h"

namespace calculator
{
class Printer
{
public:
    Printer() = default;
    ~Printer() = default;

    Printer(const Printer&) = default;
    Printer& operator=(const Printer&) = default;
    Printer(Printer&&) noexcept = default;
    Printer& operator=(Printer&&) noexcept = default;

    void print(const Context& ctx);
    void printError(const char* message);
};
} // namespace calculator
