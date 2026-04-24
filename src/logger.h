#pragma once
#include <memory>

namespace calculator
{
class Logger
{
public:
    static Logger& instance();
    void info(const char* message);
    void error(const char *message);
    void debug(const char *message);
    ~Logger();

private:
    Logger();
    Logger(const Logger&) = delete;
    Logger& operator=(const Logger&) = delete;

private:
    struct logger_impl;
    std::unique_ptr<logger_impl> m_logger;
};
}