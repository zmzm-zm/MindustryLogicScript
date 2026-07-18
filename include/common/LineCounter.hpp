#pragma once
#include <cstddef>
#include <string>

class LineCounter {
public:
    static void increment() noexcept;
    static void decrement() noexcept;
    static std::size_t getLineCount() noexcept;
private:
    static std::size_t line_;
};
