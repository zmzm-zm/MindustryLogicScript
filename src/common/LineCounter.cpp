#include <backend/logger/Logger.hpp>
#include <common/LineCounter.hpp>
std::size_t LineCounter::line_ = 0;
void LineCounter::increment_(std::string name, std::size_t line) noexcept {
    line_ += 1;
    Logger::instance()->debug("{}->increment({}): {}", name, 1, line);
}

void LineCounter::decrement_(std::string name, std::size_t line) noexcept {
    line_ -= 1;
    Logger::instance()->debug("{}->decrement({}): {}", name, 1, line);
}

std::size_t LineCounter::getLineCount() noexcept {
    return line_;
}
