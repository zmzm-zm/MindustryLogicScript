#pragma once
#include <frontend/ast/nodes/ExpressionNode.hpp>

class OperationNode final: public ExpressionNode {
public:
    OperationNode(const std::string& name,
        std::unique_ptr<ExpressionNode> left = nullptr,
        std::string value = "^v^",
        std::unique_ptr<ExpressionNode> right = nullptr);
    std::string toString() override;
private:
    friend class Parser;
};
