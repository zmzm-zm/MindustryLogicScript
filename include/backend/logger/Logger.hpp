#pragma once
#include <spdlog/spdlog.h>

class Logger {
public:
    void initialize();
    static Logger& instance();
    Logger(const Logger&) = delete;
    Logger& operator=(const Logger&) = delete;
    Logger(Logger&&) = delete;
    Logger& operator=(Logger&&) = delete;
    spdlog::logger* operator->() const;
	static void error(const std::string& msg);
private:
    Logger();
    ~Logger();
    spdlog::logger* logger_;
};
