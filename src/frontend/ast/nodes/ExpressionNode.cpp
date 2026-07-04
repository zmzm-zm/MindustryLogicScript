#include <functional>
#include <frontend/ast/nodes/ExpressionNode.hpp>
#include <frontend/lexer/Tokenizer.hpp>
ExpressionNode::ExpressionNode(const std::string& name,
    ExpressionNode* left,
    std::string value,
    ExpressionNode* right):
    left_(left), right_(right), name_(name), value_(std::move(value)) {
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
