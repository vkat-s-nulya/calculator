#pragma once
#include "types.h"

namespace calculator
{
class Printer
{
public:
    void print(const Context& ctx);
    void printError(const char* message);
};
}
