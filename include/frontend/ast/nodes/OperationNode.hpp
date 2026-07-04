#pragma once
#include <frontend/ast/nodes/ExpressionNode.hpp>

class OperationNode final: public ExpressionNode {
public:
    OperationNode(const std::string& name,
        ExpressionNode* left = nullptr,
        std::string value = "^v^",
        ExpressionNode* right = nullptr);
    std::string toString() override;
private:
    friend class Parser;
};
