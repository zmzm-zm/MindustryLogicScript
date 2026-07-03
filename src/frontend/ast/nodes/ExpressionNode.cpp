#include <functional>
#include <vector>
#include <frontend/ast/nodes/ExpressionNode.hpp>
#include <frontend/lexer/Tokenizer.hpp>

size_t ExpressionNode::size_ = 0;

ExpressionNode::ExpressionNode(const std::string& name,
    ExpressionNode* left,
    std::string value,
    ExpressionNode* right):
    name_(name), left_(left), value_(value), right_(right) {
    size_++;
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
    return left_;
}

void ExpressionNode::setLeft(ExpressionNode* left) {
    left_ = left;
}

ExpressionNode* ExpressionNode::getRight() const {
    return right_;
}

void ExpressionNode::setRight(ExpressionNode* right) {
    right_ = right;
}

OperatorType ExpressionNode::getOperatorType() const {
    return operatorType_;
}

const std::string& ExpressionNode::getName() const {
    return name_;
}
