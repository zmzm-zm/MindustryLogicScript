#include <frontend/ast/nodes/OperationNode.hpp>
#include <backend/logger/Logger.hpp>
size_t OperationNode::size_ = 0;
OperationNode::OperationNode(const std::string& left,
	std::string operator__,
	std::unique_ptr<OperationNode> right):
    left_(left), operator_(operator__), right_(std::move(right)), tmp_(left_) {
	type_ = StatementType::OPERATION;
	analyzeOperator();
	size_++;
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
void OperationNode::analyzeOperator() {
	if (operator_ == "*") operatorType_ = OperatorType::Multiplication;
	else if (operator_ == "/") operatorType_ = OperatorType::Division;
	else if (operator_ == "+") operatorType_ = OperatorType::Addition;
	else if (operator_ == "-") operatorType_ = OperatorType::Subtraction;
}

void OperationNode::sort() {
	auto next = right_.get();
	for (int i = 0; i < size_; ++i) {
		Logger::instance()->debug("OperationNode::sort()- i:" + i);
		if (next != nullptr) {
			Logger::instance()->debug("OperationNode::sort(): left: " + left_
										+ "\nnext left: " + next->left_
										+ "\noperator: " + operator_
										+ "\nnext operator: " + next->operator_);
		}
		while (next != nullptr) {
			if (operatorType_ < next->operatorType_) {
				Logger::instance()->debug(operator_ + " < " + next->operator_);
				auto tmpOperator = next->operator_;
				operator_ = next->operator_;
				next->operator_ = tmpOperator;
				auto tmpType = next->operatorType_;
				operatorType_ = next->operatorType_;
				next->operatorType_ = tmpType;
				auto tmpLeft = next->left_;
				left_ = next->left_;
				next->left_ = tmpLeft;
			}
			next = next->right_.get();
		}
	}
}
