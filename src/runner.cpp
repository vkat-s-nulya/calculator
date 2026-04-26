#include "runner.h"
#include "exceptions.h"
#include "logger.h"
#include <iostream>

namespace calculator
{

Runner::Runner(const std::string& conninfo)
    : m_database(conninfo)
{
    warmupCache();
}

void Runner::warmupCache()
{
    auto records = m_database.loadAll();
    for (const auto& r : records)
    {
        std::string key = Cache::buildKey(r.a, r.b, r.operation);
        m_cache.insert(key, {r.result, r.status});
    }
    Logger::instance().info(("cache warmed up with " + std::to_string(m_cache.size()) + " records").c_str());
}

int Runner::run(int argc, char* argv[])
{
    if (argc < 2)
    {
        m_printer.printError("JSON input is required");
        std::cerr << "Usage: calculator '{\"a\": NUM, \"b\": NUM, \"op\": \"add|sub|mul|div|pow|fac\"}'" << std::endl;
        return 1;
    }

    try
    {
        Context ctx = m_parser.parse(argv[1]);
        std::string key = Cache::buildKey(ctx.a, ctx.b, ctx.operation);

        auto cached = m_cache.find(key);
        if (cached.has_value())
        {
            Logger::instance().info("cache hit");
            if (cached->status != 0)
            {
                throw CalculationError("cached error (status " + std::to_string(cached->status) + ")");
            }
            ctx.result = cached->result;
            m_printer.print(ctx);
            return 0;
        }

        Logger::instance().info("cache miss");

        try
        {
            m_checker.check(ctx);
            m_calculator.calculate(ctx);
        }
        catch (const ValidationError&)
        {
            saveError(ctx, key);
            throw;
        }
        catch (const CalculationError&)
        {
            saveError(ctx, key);
            throw;
        }

        CalculationRecord record{ctx.a, ctx.b, ctx.operation, ctx.result, 0};
        m_database.save(record);
        m_cache.insert(key, {ctx.result, 0});

        m_printer.print(ctx);
        return 0;
    }
    catch (const CalculatorException& e)
    {
        m_printer.printError(e.what());
        return 1;
    }
}

void Runner::saveError(const Context& ctx, const std::string& key)
{
    CalculationRecord record{ctx.a, ctx.b, ctx.operation, 0, 1};
    m_database.save(record);
    m_cache.insert(key, {0, 1});
}

}
