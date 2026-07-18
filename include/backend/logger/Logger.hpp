#pragma once
#include <spdlog/spdlog.h>

class Logger {
    enum class Level;
public:
    void initialize();
    static Logger& instance();
    Logger(const Logger&) = delete;
    Logger& operator=(const Logger&) = delete;
    Logger(Logger&&) = delete;
    Logger& operator=(Logger&&) = delete;
    spdlog::logger* operator->() const;
#define debug(msg, ...) \
    Logger::instance()->debug(std::format("[{}:{}] " msg, __FILE_NAME__, __LINE__ __VA_OPT__(,) __VA_ARGS__))
#define info(msg, ...) \
    Logger::instance()->info(std::format("[{}:{}] " msg, __FILE_NAME__, __LINE__ __VA_OPT__(,) __VA_ARGS__))
#define error(msg, ...) \
    Logger::instance()->error(std::format("[{}:{}] " msg, __FILE_NAME__, __LINE__ __VA_OPT__(,) __VA_ARGS__))
private:
    enum class Level {
        DEBUG_,
        INFO_,
        ERROR_,
    };
    Logger();
    ~Logger();
    spdlog::logger* logger_;
};
