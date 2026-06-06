#include <backend/logger/Logger.hpp>
#include <spdlog/sinks/rotating_file_sink.h>

Logger::Logger() {
    initialize();
}
Logger::~Logger() {

}
Logger& Logger::instance() {
    static Logger instance;
    return instance;
}
spdlog::logger* Logger::operator->() {
    return _logger;
}
void Logger::initialize() {
    _logger = spdlog::rotating_logger_st("logger",
        "./logs/.log",
        2048 * 1024,
        2).get();
    _logger->set_level(spdlog::level::debug);
}