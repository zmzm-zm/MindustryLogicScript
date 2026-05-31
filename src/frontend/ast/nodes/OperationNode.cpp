#include <frontend/ast/nodes/OperationNode.hpp>
OperationNode::OperationNode(const std::string& left,
	std::string operator__,
	std::unique_ptr<OperationNode> right):
    left_(left), operator_(operator__), right_(std::move(right)), tmp_(left_) {
	type_ = StatementType::OPERATION;
}
std::string OperationNode::toString() {
	if (right_ == nullptr) {
			return "";
	}
	if (operator_ == "*") {
		operator_ = "mul";
	} else if (operator_ == "/") {
		operator_ = "div";
	} else if (operator_ == "+" || operator_ == "=") {
		operator_ = "add";
	} else if (operator_ == "-") {
		operator_ = "sub";
	}
	right_->tmp_ = tmp_;
	return "op " + operator_ + " " + tmp_ + " " + tmp_ + " " + right_->left_ + "\n" + right_->toString();
}
const std::string& OperationNode::getLeft() const {
	return left_;
}
const std::unique_ptr<OperationNode>& OperationNode::getRight() const {
	return right_;
}
const std::string& OperationNode::getOperator() const {
	return operator_;
}