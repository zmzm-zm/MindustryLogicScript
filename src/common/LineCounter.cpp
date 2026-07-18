#include <backend/logger/Logger.hpp>
#include <common/LineCounter.hpp>
std::size_t LineCounter::line_ = 0;
void LineCounter::increment() noexcept {
    line_ += 1;
    Logger::debug("increment()");
}

void LineCounter::decrement() noexcept {
    line_ -= 1;
    Logger::debug("decrement()");
}

std::size_t LineCounter::getLineCount() noexcept {
    return line_;
}
