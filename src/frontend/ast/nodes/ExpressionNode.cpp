#include <frontend/ast/nodes/ExpressionNode.hpp>
#include <frontend/lexer/Tokenizer.hpp>

size_t ExpressionNode::size_ = 0;

ExpressionNode::ExpressionNode(const std::string& name,
    ExpressionNode* left,
    std::string value,
    ExpressionNode* right):
    name_(name), left_(left), value_(value), right_(right) {
    type_ = StatementType::OPERATION;
    size_++;
    operatorType_ = Tokenizer::analyzeOperator(value_);
}

ExpressionNode::~ExpressionNode() {
}

std::string ExpressionNode::toString() {
    std::vector<std::string> lines;
    
    std::function<std::string(const ExpressionNode*)> traverse = 
        [&](const ExpressionNode* node) -> std::string {
            if (!node) return "";
            
            // 叶子节点（数字或变量）
            if (!node->left_ && !node->right_) {
                return node->value_;
            }
            
            std::string leftVar = traverse(node->left_);
            std::string rightVar = traverse(node->right_);
            
            std::string op;
            if (node->value_ == "+") op = "add";
            else if (node->value_ == "-") op = "sub";
            else if (node->value_ == "*") op = "mul";
            else if (node->value_ == "/") op = "div";
            else if (node->value_ == "%") op = "mod";
            else op = node->value_;
            
            lines.push_back("op " + op + " " + node->name_ + " " + leftVar + " " + rightVar);
            
            return node->name_;
        };
    
    std::string resultVar = traverse(this);
    
    // 如果是单元表达式（没有生成任何op指令），需要特殊处理
    if (lines.empty()) {
        // 直接返回叶子节点的值，不生成op指令
        return "";
    }
    
    std::string result;
    for (const auto& line : lines) {
        result += line + "\n";
    }
    return result;
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
