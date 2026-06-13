#include <frontend/ast/nodes/AssignmentNode.hpp>
#include <string>
#include <utility>
AssignmentNode::AssignmentNode(std::string variable, std::unique_ptr<ExpressionNode> value):variable_(variable), value_(std::move(value)){} 

std::string AssignmentNode::toString() {
	auto exprCode = value_->toString();
	if (exprCode.empty()) return "set " + variable_  + " " + value_->getValue() + "\n";
	return exprCode + "set " + variable_ + " " + value_->getName() + "\n";
}
