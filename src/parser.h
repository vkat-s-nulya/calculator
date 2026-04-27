#pragma once

#include "types.h"
#include <string>

namespace calculator
{
class Parser
{
public:
    Parser() = default;
    ~Parser() = default;

    Parser(const Parser&) = default;
    Parser& operator=(const Parser&) = default;
    Parser(Parser&&) = default;
    Parser& operator=(Parser&&) = default;

    Context parse(const std::string& input);
};
} // namespace calculator