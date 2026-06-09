#include <frontend/ast/nodes/AssignmentNode.hpp>
#include <frontend/ast/nodes/ExpressionNode.hpp>

AssignmentNode::AssignmentNode(const std::string& variable, std::unique_ptr<ExpressionNode> value):
    variable_(variable), value_(std::move(value)) {
    type_ = StatementType::ASSIGNMENT;
}

std::string AssignmentNode::toString() {
    std::string exprCode = value_->toString();
    
    if (exprCode.empty()) {
        
        return "set " + variable_ + " " + value_->getValue() + "\n";
    }
    
    
    return "set " + variable_ + " 0\n" + exprCode + "set " + variable_ + " " + value_->getName() + "\n";
}
std::string AssignmentNode::getVar() const {
	return variable_;
}