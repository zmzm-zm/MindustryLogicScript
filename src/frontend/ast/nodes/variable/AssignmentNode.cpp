#include <frontend/ast/nodes/variable/VariableNode.hpp>
#include <frontend/ast/nodes/variable/AssignmentNode.hpp>
#include <string>
#include <utility>
AssignmentNode::AssignmentNode(const std::string& variable, std::unique_ptr<ExpressionNode> value): VariableNode(variable, std::move(value)) {}
std::string AssignmentNode::toString() {
	auto exprCode = value_->toString();
	if (exprCode.empty()) return "set " + variable_  + " " + value_->getValue() + "\n";
	return exprCode + "set " + variable_ + " " + value_->getName() + "\n";
}
