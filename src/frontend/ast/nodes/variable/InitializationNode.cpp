#include <frontend/ast/nodes/variable/VariableNode.hpp>
#include <frontend/ast/nodes/variable/InitializationNode.hpp>
#include <string>
#include <utility>
InitializationNode::InitializationNode(std::string variable, std::unique_ptr<ExpressionNode> value)
: VariableNode(std::move(variable), std::move(value)) {}
std::string InitializationNode::toString() {
    const std::string exprCode = value_->toString();
    if (exprCode.empty()) {
        return "set " + variable_ + " " + value_->getValue() + "\n";
    }
    return "set " + variable_ + " 0\n" + exprCode + "set " + variable_ + " " + value_->getName() + "\n";
}
