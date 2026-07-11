#pragma once
#include <cstddef>
#include <string>

class LineCounter {
public:
#define increment() increment_(__FILE_NAME__, __LINE__)
    static void increment_(std::string name = "", std::size_t line = 0) noexcept;
#define decrement() decrement_(__FILE_NAME__, __LINE__)
    static void decrement_(std::string name = "", std::size_t line = 0) noexcept;
    static std::size_t getLineCount() noexcept;
private:
    static std::size_t line_;
};
