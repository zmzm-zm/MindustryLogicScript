#include <functional>
#include <frontend/ast/nodes/ExpressionNode.hpp>
#include <frontend/lexer/Tokenizer.hpp>
ExpressionNode::ExpressionNode(const std::string& name,
    std::unique_ptr<ExpressionNode> left,
    std::string value,
    std::unique_ptr<ExpressionNode> right):
    left_(std::move(left)), right_(std::move(right)), name_(name), value_(std::move(value)) {
    operatorType_ = Tokenizer::analyzeOperator(value_);
}

ExpressionNode::~ExpressionNode() {
}

std::string ExpressionNode::toString() {
    return "ExpressionNode::toString: An Unexpected calling";
}
const std::string& ExpressionNode::getValue() const {
    return value_;
}

ExpressionNode* ExpressionNode::getLeft() const {
    return left_.get();
}

void ExpressionNode::setLeft(std::unique_ptr<ExpressionNode> left) {
    left_ = std::move(left);
}

ExpressionNode* ExpressionNode::getRight() const {
    return right_.get();
}

void ExpressionNode::setRight(std::unique_ptr<ExpressionNode> right) {
    right_ = std::move(right);
}

OperatorType ExpressionNode::getOperatorType() const {
    return operatorType_;
}

const std::string& ExpressionNode::getName() const {
    return name_;
}
