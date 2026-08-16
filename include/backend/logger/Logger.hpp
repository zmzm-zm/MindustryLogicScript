#pragma once
#include <spdlog/spdlog.h>

/**
 * @defgroup Logger Logger
 * @ingroup Backend
 * @brief Wraps a spdlog logger as a singleton for application-wide logging.
 */

/** @ingroup Logger
 *  @brief Wraps a spdlog logger as a singleton for application-wide logging.
 */
class Logger {
public:
    /** @brief Initializes the underlying spdlog logger. */
    void initialize();

    /**
     * @brief Returns the singleton Logger instance.
     * @return A reference to the single Logger instance.
     */
    static Logger& instance();

    /// @brief Copy constructor is deleted (singleton).
    Logger(const Logger&) = delete;
    /// @brief Copy assignment is deleted (singleton).
    Logger& operator=(const Logger&) = delete;
    /// @brief Move constructor is deleted (singleton).
    Logger(Logger&&) = delete;
    /// @brief Move assignment is deleted (singleton).
    Logger& operator=(Logger&&) = delete;

    /**
     * @brief Provides arrow access to the underlying spdlog logger.
     * @return The underlying spdlog logger pointer.
     */
    spdlog::logger* operator->() const;

    /** @brief Logs a debug message with a file and line prefix. */
#define debug(msg, ...) \
    Logger::instance()->debug(std::format("[{}:{}] " msg, __FILE_NAME__, __LINE__ __VA_OPT__(,) __VA_ARGS__))
    /** @brief Logs an info message with a file and line prefix. */
#define info(msg, ...) \
    Logger::instance()->info(std::format("[{}:{}] " msg, __FILE_NAME__, __LINE__ __VA_OPT__(,) __VA_ARGS__))
    /** @brief Logs an error message with a file and line prefix. */
#define error(msg, ...) \
    Logger::instance()->error(std::format("[{}:{}] " msg, __FILE_NAME__, __LINE__ __VA_OPT__(,) __VA_ARGS__))

private:
    Logger();  ///< @brief Private default constructor (singleton).
    ~Logger(); ///< @brief Private destructor (singleton).

    spdlog::logger* logger_; ///< The underlying spdlog logger.
};
