#include <backend/logger/Logger.hpp>
#include <spdlog/sinks/rotating_file_sink.h>
#include <string>

Logger::Logger() {
    initialize();
}
Logger::~Logger() {

}
void Logger::initialize() {
	logger_ = spdlog::rotating_logger_st("logger",
        "./logs/.log",
        2048 * 1024,
        2).get();
    logger_->set_level(spdlog::level::debug);
}
Logger& Logger::instance() {
    static Logger instance;
    return instance;
}
spdlog::logger* Logger::operator->() {
    return logger_;
}
void Logger::error(std::string msg) {
	instance()->error(msg);
	throw std::runtime_error(msg);
}
