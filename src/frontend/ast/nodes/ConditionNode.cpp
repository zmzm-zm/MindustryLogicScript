#include <frontend/ast/nodes/ConditionNode.hpp>
#include <backend/logger/Logger.hpp>
ConditionNode::ConditionNode(
    const std::string& name,
    std::unique_ptr<ExpressionNode> left,
    std::string value,
    std::unique_ptr<ExpressionNode> right)
: ExpressionNode(name, std::move(left), value, std::move(right)){

}
std::string ConditionNode::toString() {
    // 左边没有，右边也一定没有
    if (left_ == nullptr) return "equal " + value_ + " true";
    std::string op;
    if (value_ == "<") op = "greaterThanEq";
    else if (value_ == "<=") op = "greaterThan";
    else if (value_ == ">") op = "lessThanEq";
    else if (value_ == ">=") op = "lessThan";
    else if (value_ == "==") op = "notEqual";
    else if (value_ == "===") op = "notEqual";
    else if (value_ == "!=") op = "equal";
    else if (value_ == "true") op = "always";
    else Logger::error("Unknown operator: " + value_);
    return op + " " + left_->getValue() + " " + right_->getValue();
}
void ConditionNode::setNum(const unsigned short num) noexcept {
    num_ = num;
}
unsigned short ConditionNode::getNum(unsigned short& num) const noexcept {
    return num_;
}

