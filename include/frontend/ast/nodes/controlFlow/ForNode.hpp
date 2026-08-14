#pragma once
#include "ControlFlow.hpp"
#include <frontend/ast/nodes/variable/VariableNode.hpp>

class ForNode final: public ControlFlow {
public:
    ForNode(std::unique_ptr<VariableNode> initialization,
        std::unique_ptr<ConditionNode> condition,
        std::unique_ptr<VariableNode> expression,
        std::unique_ptr<AstNode> body,
        std::size_t line);
    std::string toString() override;
private:
    std::unique_ptr<VariableNode> initialization_;
    std::unique_ptr<VariableNode> expression_;
};/**/
