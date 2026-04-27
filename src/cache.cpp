#include "cache.h"
#include <algorithm>

namespace calculator
{

std::string Cache::buildKey(int64_t a, int64_t b, Operation op)
{
    if (op == Operation::FAC)
    {
        return std::to_string(a) + toString(op);
    }

    if (op == Operation::ADD || op == Operation::MUL)
    {
        if (a > b)
        {
            std::swap(a, b);
        }
    }

    return std::to_string(a) + toString(op) + std::to_string(b);
}

std::optional<Context> Cache::find(const Context& ctx) const
{
    const std::string key = buildKey(ctx.a, ctx.b, ctx.operation);
    const auto it = m_data.find(key);
    if (it == m_data.end())
    {
        return std::nullopt;
    }
    return it->second;
}

void Cache::insert(const Context& ctx)
{
    const std::string key = buildKey(ctx.a, ctx.b, ctx.operation);
    m_data[key] = ctx;
}

size_t Cache::size() const { return m_data.size(); }

} // namespace calculator
