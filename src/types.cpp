#include "types.h"
#include <unordered_map>

namespace calculator
{

static const std::unordered_map<Operation, std::string> kOpToString = {
    {Operation::ADD, "add"}, {Operation::SUB, "sub"}, {Operation::MUL, "mul"},
    {Operation::DIV, "div"}, {Operation::POW, "pow"}, {Operation::FAC, "fac"},
};

static const std::unordered_map<std::string, Operation> kStringToOp = {
    {"add", Operation::ADD}, {"sub", Operation::SUB}, {"mul", Operation::MUL},
    {"div", Operation::DIV}, {"pow", Operation::POW}, {"fac", Operation::FAC},
};

std::string toString(Operation op) { return kOpToString.at(op); }

std::optional<Operation> fromString(const std::string& s)
{
    const auto it = kStringToOp.find(s);
    if (it == kStringToOp.end())
    {
        return std::nullopt;
    }
    return it->second;
}

} // namespace calculator
