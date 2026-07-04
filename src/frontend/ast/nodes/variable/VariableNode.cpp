#include <frontend/ast/nodes/variable/VariableNode.hpp>

VariableNode::VariableNode(std::string variable, std::unique_ptr<ExpressionNode> value)
: variable_(std::move(variable)), value_(std::move(value)) {}
std::string VariableNode::getVar() const {
	return variable_;
}
