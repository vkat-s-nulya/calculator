#include "logger.h"
#include <spdlog/spdlog.h>
#include <spdlog/sinks/stdout_color_sinks.h>

namespace calculator
{

struct Logger::logger_impl
{
    std::shared_ptr<spdlog::logger> logger;
};

Logger::Logger() : m_logger(std::make_unique<logger_impl>())
{
    m_logger->logger = spdlog::stdout_color_mt("calculator");
    m_logger->logger->set_level(spdlog::level::debug);
}

Logger::~Logger() = default;

Logger& Logger::instance()
{
    static Logger logger;
    return logger;
}

void Logger::info(const char* message)  { m_logger->logger->info(message); }
void Logger::error(const char* message) { m_logger->logger->error(message); }
void Logger::debug(const char* message) { m_logger->logger->debug(message); }

}
