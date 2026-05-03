#include "runner.h"
#include "exceptions.h"
#include "logger.h"
#include <nlohmann/json.hpp>

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
        ("cache warmed up with " + std::to_string(m_cache.size()) + " records").c_str());
}

std::string Runner::process(const std::string& request)
{
    nlohmann::json response;

    try
    {
        Context ctx = m_parser.parse(request);

        const auto cached = m_cache.find(ctx);
        if (cached.has_value())
        {
            Logger::instance().info("cache hit");
            response["result"] = cached->result;
            response["status"] = cached->status;
            if (cached->status != 0)
            {
                response["error"] = "cached error";
            }
            return response.dump() + "\n";
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

        response["result"] = ctx.result;
        response["status"] = 0;
    }
    catch (const CalculatorException& e)
    {
        Logger::instance().error(e.what());
        response["result"] = 0;
        response["status"] = 1;
        response["error"] = e.what();
    }

    return response.dump() + "\n";
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
