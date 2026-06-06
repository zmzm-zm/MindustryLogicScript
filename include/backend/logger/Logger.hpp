#pragma once
#include <spdlog/spdlog.h>

class Logger {
public:
    static Logger& instance();
    Logger(const Logger&) = delete;
    Logger& operator=(const Logger&) = delete;
    Logger(Logger&&) = delete;
    Logger& operator=(Logger&&) = delete;
    spdlog::logger* operator->();
    void initialize();
private:
    Logger();
    ~Logger();
    spdlog::logger* _logger;
};
