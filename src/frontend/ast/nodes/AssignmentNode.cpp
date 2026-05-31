#include <frontend/ast/nodes/AssignmentNode.hpp>
AssignmentNode::AssignmentNode(const std::string& variable, const std::string& value):
    variable_(variable), value_(value) {
    type_ = StatementType::ASSIGNMENT;
}
std::string AssignmentNode::toString() {
	return "set " + variable_ + " " + value_ + "\n";
}
const std::string& AssignmentNode::getVariable() const {
	return variable_;
}
const std::string& AssignmentNode::getValue() const {
	return value_;
}