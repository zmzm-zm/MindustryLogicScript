#pragma once
#include <frontend/ast/nodes/controlFlow/ControlFlow.hpp>
class IfNode final: public ControlFlow {
public:
    IfNode(std::unique_ptr<ConditionNode> condition, std::unique_ptr<AstNode> body, std::size_t line);
    std::string toString() override;
private:
    std::size_t selfLine_ = 0;
    std::string conditionStr_ = "";
};