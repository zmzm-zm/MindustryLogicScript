#pragma once
#include <cstddef>
#include <string>

/**
 * @defgroup Common Common
 * @ingroup Core
 * @brief Shared utilities used across the compiler.
 */

/** @ingroup Common
 *  @brief Tracks the current output line number while generating Mindustry logic.
 */
class LineCounter {
public:
    /** @brief Increases the tracked line count by one. */
    static void increment() noexcept;

    /** @brief Decreases the tracked line count by one. */
    static void decrement() noexcept;

    /**
     * @brief Returns the currently tracked line count.
     * @return The number of lines counted so far.
     */
    static std::size_t getLineCount() noexcept;

private:
    /// The internal counter value shared by all instances.
    static std::size_t line_;
};
