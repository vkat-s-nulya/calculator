#include "printer.h"
#include "logger.h"
#include <iostream>

namespace calculator
{
void Printer::print(const Context& ctx)
{
    Logger::instance().debug("printing result");
    std::cout << "Result: " << ctx.result << std::endl;
}

void Printer::printError(const char* message)
{
    Logger::instance().error(message);
    std::cerr << "Error: " << message << std::endl;
}
}
