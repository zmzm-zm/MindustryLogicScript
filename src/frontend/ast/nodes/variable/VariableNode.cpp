#include <frontend/ast/nodes/variable/VariableNode.hpp>

VariableNode::VariableNode(const std::string& variable, std::unique_ptr<ExpressionNode> value): variable_(variable), value_(std::move(value)) {}
std::string VariableNode::getVar() const {
	return variable_;
}
