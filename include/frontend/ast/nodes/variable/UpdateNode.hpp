#pragma once
#include "VariableNode.hpp"

class UpdateNode final: public VariableNode {
public:
    UpdateNode(std::string var, std::string op, std::unique_ptr<ExpressionNode> value = nullptr);
    UpdateNode(std::string var, std::string op, std::string ident);
    std::string toString() override;
private:
    std::string op_ = "^v^";
    std::string ident_ = "^v^";
};
