#pragma once
#include <stdexcept>

namespace calculator
{
class CalculatorException : public std::runtime_error
{
public:
    using std::runtime_error::runtime_error;
};

class ParseError : public CalculatorException
{
public:
    using CalculatorException::CalculatorException;
};

class ValidationError : public CalculatorException
{
public:
    using CalculatorException::CalculatorException;
};

class CalculationError : public CalculatorException
{
public:
    using CalculatorException::CalculatorException;
};

class DatabaseError : public CalculatorException
{
public:
    using CalculatorException::CalculatorException;
};
} // namespace calculator