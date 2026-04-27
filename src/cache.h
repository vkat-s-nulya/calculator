#pragma once
#include "types.h"
#include <optional>
#include <string>
#include <unordered_map>

namespace calculator
{

class Cache
{
public:
    Cache() = default;
    ~Cache() = default;

    Cache(const Cache&) = default;
    Cache& operator=(const Cache&) = default;
    Cache(Cache&&) noexcept = default;
    Cache& operator=(Cache&&) noexcept = default;

    std::optional<Context> find(const Context& ctx) const;
    void insert(const Context& ctx);
    size_t size() const;

private:
    static std::string buildKey(int64_t a, int64_t b, Operation op);

    std::unordered_map<std::string, Context> m_data;
};

} // namespace calculator
