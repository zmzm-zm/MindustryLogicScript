#include <functional>
#include <vector>
#include <frontend/ast/nodes/OperationNode.hpp>
#include <frontend/ast/nodes/ExpressionNode.hpp>
OperationNode::OperationNode(const std::string& name, ExpressionNode* left, std::string value, ExpressionNode* right)
: ExpressionNode(name, left, std::move(value), right)
{
}

std::string OperationNode::toString() {
    std::vector<std::string> lines;
    std::function<std::string(const ExpressionNode*)> traverse =
        [&](const ExpressionNode* node) -> std::string {
            if (!node) return "";
            if (!node->getLeft() && !node->getRight()) {
                return node->getValue();
            }
            std::string leftVar = traverse(node->getLeft());
            std::string rightVar = traverse(node->getRight());
            std::string op;
            if (node->getValue() == "+") op = "add";
            else if (node->getValue() == "-") op = "sub";
            else if (node->getValue() == "*") op = "mul";
            else if (node->getValue() == "/") op = "div";
            else if (node->getValue() == "%") op = "mod";
            else op = node->getValue();
            lines.push_back("op " + op + " " + node->getName() + " " + leftVar + " " + rightVar);
            return node->getName();
    };
    std::string resultVar = traverse(this);
    if (lines.empty()) {
        return "";
    }
    std::string result;
    for (const auto& line : lines) {
        result += line + "\n";
    }
    return result;
}
