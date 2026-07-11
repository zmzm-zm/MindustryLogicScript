#include <frontend/ast/nodes/controlFlow/ControlFlow.hpp>
ControlFlow::ControlFlow(std::unique_ptr<ConditionNode> condition, std::unique_ptr<AstNode> body)
: condition_(std::move(condition)), body_(std::move(body)) {}

std::string ControlFlow::toString() {
    return "ControlFlow::toString: An Unexpected calling";
}
