#include "runner.h"
#include "exceptions.h"
#include "logger.h"
#include <iostream>

namespace calculator
{

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
        m_checker.check(ctx);
        m_calculator.calculate(ctx);
        m_printer.print(ctx);
        return 0;
    }
    catch (const CalculatorException& e)
    {
        m_printer.printError(e.what());
        return 1;
    }
}
}