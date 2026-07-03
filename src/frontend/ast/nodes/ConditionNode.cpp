#include <frontend/ast/nodes/ConditionNode.hpp>
#include <backend/logger/Logger.hpp>
ConditionNode::ConditionNode(const std::string& name, ExpressionNode* left, std::string value, ExpressionNode* right)
: ExpressionNode(name, left, value, right){

}
std::string ConditionNode::toString() {
    if (left_ == nullptr) return "equal " + value_ + " true";
    std::string op;
    if (value_ == "<") op = "lessThan";
    else if (value_ == "<=") op = "lessThanEq";
    else if (value_ == ">") op = "greaterThan";
    else if (value_ == ">=") op = "greaterThanEq";
    else if (value_ == "==") op = "equal";
    else if (value_ == "===") op = "strictEqual";
    else if (value_ == "!=") op = "notEqual";
    else if (value_ == "true") op = "always";
    else Logger::error("Unknown operator: " + value_);
    return op + " " + left_->toString() + " " + right_->toString();
}
void ConditionNode::setNum(unsigned short num) noexcept {
    num_ = num;
}
unsigned short ConditionNode::getNum(unsigned short& num) const noexcept {
    return num_;
}

