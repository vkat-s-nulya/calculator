#pragma once
#include "cache.h"
#include "calculator.h"
#include "checker.h"
#include "database.h"
#include "parser.h"
#include "printer.h"
#include <string>

namespace calculator
{

class Runner
{
public:
    explicit Runner(const std::string& conninfo);
    ~Runner() = default;

    Runner(const Runner&) = delete;
    Runner& operator=(const Runner&) = delete;
    Runner(Runner&&) = delete;
    Runner& operator=(Runner&&) = delete;

    int run(int argc, char* argv[]);

private:
    void warmupCache();
    void saveError(const Context& ctx);

    Parser m_parser;
    Checker m_checker;
    Calculator m_calculator;
    Printer m_printer;
    PostgresDatabase m_database;
    Cache m_cache;
};

} // namespace calculator
