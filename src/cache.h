#pragma once
#include "types.h"
#include <optional>
#include <string>
#include <unordered_map>

namespace calculator
{

struct CalculationResult
{
    int64_t result;
    int status;
};

class Cache
{
public:
    static std::string buildKey(int64_t a, int64_t b, Operation op);

    std::optional<CalculationResult> find(const std::string& key) const;
    void insert(const std::string& key, const CalculationResult& value);
    size_t size() const;

private:
    std::unordered_map<std::string, CalculationResult> m_data;
};

}
