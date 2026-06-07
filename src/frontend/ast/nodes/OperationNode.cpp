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
	if (right_ == nullptr) return;
	std::vector<OperationNode*> nodes;
	OperationNode* current = this;
	while (current != nullptr) {
		nodes.push_back(current);
		current = current->right_.get();
	}
	bool swapped = false;
	for (size_t i = 0; i < nodes.size() - 1; ++i) {
		swapped = false;
		for (size_t j = 0; j < nodes.size() - i - 1; ++j) {
			if (nodes[j]->operatorType_ > nodes[j+1]->operatorType_) {
				std::swap(nodes[j]->left_, nodes[j+1]->left_);
				std::swap(nodes[j]->operator_, nodes[j+1]->operator_);
				std::swap(nodes[j]->operatorType_, nodes[j+1]->operatorType_);
				swapped = true;
			}
		}
		if (!swapped) break;
	}
}
