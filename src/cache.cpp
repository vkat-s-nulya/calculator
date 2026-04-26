#include "cache.h"
#include <algorithm>

namespace calculator
{

static const char* opToString(Operation op)
{
    switch (op)
    {
    case Operation::ADD: return "+";
    case Operation::SUB: return "-";
    case Operation::MUL: return "*";
    case Operation::DIV: return "/";
    case Operation::POW: return "^";
    case Operation::FAC: return "!";
    }
    return "?";
}

std::string Cache::buildKey(int64_t a, int64_t b, Operation op)
{
    if (op == Operation::FAC)
    {
        return std::to_string(a) + "!";
    }

    if (op == Operation::ADD || op == Operation::MUL)
    {
        if (a > b)
        {
            std::swap(a, b);
        }
    }

    return std::to_string(a) + opToString(op) + std::to_string(b);
}

std::optional<CalculationResult> Cache::find(const std::string& key) const
{
    auto it = m_data.find(key);
    if (it == m_data.end())
    {
        return std::nullopt;
    }
    return it->second;
}

void Cache::insert(const std::string& key, const CalculationResult& value)
{
    m_data[key] = value;
}

size_t Cache::size() const
{
    return m_data.size();
}

}
