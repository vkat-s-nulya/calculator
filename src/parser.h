#pragma once

#include <string>
#include "types.h"

namespace calculator
{
class Parser
{
public:
    Context parse(const std::string& input);

private:
    Operation parseOperation(const std::string& operation);
};
}