#include "runner.h"
#include "exceptions.h"
#include "logger.h"
#include <iostream>

namespace calculator
{

Runner::Runner(const std::string& conninfo) : m_database(conninfo)
{
    warmupCache();
}

void Runner::warmupCache()
{
    const auto records = m_database.loadAll();
    for (const auto& ctx : records)
    {
        m_cache.insert(ctx);
    }
    Logger::instance().info(
        ("cache warmed up with " + std::to_string(m_cache.size()) + " records")
            .c_str());
}

int Runner::run(int argc, char* argv[])
{
    if (argc < 2)
    {
        m_printer.printError("JSON input is required");
        std::cerr << "Usage: calculator '{\"a\": NUM, \"b\": NUM, \"op\": "
                     "\"add|sub|mul|div|pow|fac\"}'"
                  << std::endl;
        return 1;
    }

    try
    {
        Context ctx = m_parser.parse(argv[1]);

        const auto cached = m_cache.find(ctx);
        if (cached.has_value())
        {
            Logger::instance().info("cache hit");
            if (cached->status != 0)
            {
                throw CalculationError("cached error (status " +
                                       std::to_string(cached->status) + ")");
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
        catch (const CalculatorException&)
        {
            saveError(ctx);
            throw;
        }

        ctx.status = 0;
        m_database.save(ctx);
        m_cache.insert(ctx);

        m_printer.print(ctx);
        return 0;
    }
    catch (const CalculatorException& e)
    {
        m_printer.printError(e.what());
        return 1;
    }
}

void Runner::saveError(const Context& ctx)
{
    Context errored = ctx;
    errored.result = 0;
    errored.status = 1;
    m_database.save(errored);
    m_cache.insert(errored);
}

} // namespace calculator
