#include "checker.h"
#include "exceptions.h"
#include "logger.h"

namespace calculator
{
void Checker::check(const Context& ctx)
{
    Logger::instance().debug("validating input");

    if (ctx.operation == Operation::DIV && ctx.b == 0)
    {
        throw ValidationError("division by zero");
    }
    if (ctx.operation == Operation::POW && ctx.b < 0)
    {
        throw ValidationError("negative exponent is not supported");
    }
    if (ctx.operation == Operation::FAC && ctx.a < 0)
    {
        throw ValidationError("factorial of negative number is not defined");
    }
}
}
