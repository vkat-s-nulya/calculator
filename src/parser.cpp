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

    Context ctx;
    ctx.a = j["a"].get<int64_t>();
    ctx.operation = parseOperation(j["op"].get<std::string>());

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

Operation Parser::parseOperation(const std::string& op)
{
    if (op == "add") return Operation::ADD;
    if (op == "sub") return Operation::SUB;
    if (op == "mul") return Operation::MUL;
    if (op == "div") return Operation::DIV;
    if (op == "pow") return Operation::POW;
    if (op == "fac") return Operation::FAC;

    throw ParseError("unknown operation: " + op);
}
}
