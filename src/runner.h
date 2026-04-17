#pragma once
#include "calculator.h"
#include "checker.h"
#include "parser.h"
#include "printer.h"

namespace calculator
{
class Runner
{
public:
    int run(int argc, char* argv[]);

private:
    Parser m_parser;
    Checker m_checker;
    Calculator m_calculator;
    Printer m_printer;
};
}