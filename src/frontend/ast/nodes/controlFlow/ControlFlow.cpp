#include <backend/logger/Logger.hpp>
#include <frontend/ast/nodes/controlFlow/ControlFlow.hpp>
ControlFlow::ControlFlow(std::unique_ptr<ConditionNode> condition, std::unique_ptr<AstNode> body, std::size_t line)
: condition_(std::move(condition)), body_(std::move(body)), selfLine_(line) {
    conditionStr_ = condition_->toString();
    Logger::debug("ControlFlow::selfLine={}", selfLine_);
}

std::string ControlFlow::toString() {
    return "ControlFlow::toString: An Unexpected calling";
}
