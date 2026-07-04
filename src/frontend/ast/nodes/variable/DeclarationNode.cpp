#include <frontend/ast/nodes/variable/VariableNode.hpp>
#include <frontend/ast/nodes/variable/DeclarationNode.hpp>
#include <frontend/ast/nodes/ExpressionNode.hpp>
#include <memory>
#include <string>
DeclarationNode::DeclarationNode(std::string variable)
: VariableNode(std::move(variable), std::make_unique<ExpressionNode>("N/A", nullptr)) {}
std::string DeclarationNode::toString() {
	return "set " + variable_ + " -1027\n";
}
std::string DeclarationNode::getVar() const {
	return variable_;
}
