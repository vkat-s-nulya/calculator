#include "parser.h"
#include "exceptions.h"
#include "logger.h"
#include <nlohmann/json.hpp>

namespace calculator
{

Context Parser::parse(const std::string& input)
{
    Logger::instance().debug("parsing JSON input");

    nlohmann::json j;
    try
    {
        j = nlohmann::json::parse(input);
    }
    catch (const nlohmann::json::parse_error& e)
    {
        throw ParseError(std::string("invalid JSON: ") + e.what());
    }

    if (!j.contains("op"))
    {
        throw ParseError("missing field: op");
    }
    if (!j.contains("a"))
    {
        throw ParseError("missing field: a");
    }

    const auto op = fromString(j["op"].get<std::string>());
    if (!op.has_value())
    {
        throw ParseError("unknown operation: " + j["op"].get<std::string>());
    }

    Context ctx;
    ctx.a = j["a"].get<int64_t>();
    ctx.operation = op.value();

    if (ctx.operation != Operation::FAC)
    {
        if (!j.contains("b"))
        {
            throw ParseError("missing field: b");
        }
        ctx.b = j["b"].get<int64_t>();
    }
    else
    {
        ctx.b = 0;
    }

    return ctx;
}

} // namespace calculator
