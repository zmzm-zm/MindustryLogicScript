#pragma once
#include <memory>
#include <frontend/ast/nodes/AstNode.hpp>
#include <frontend/ast/nodes/StatementNode.hpp>
#include <frontend/ast/nodes/ConditionNode.hpp>
class ControlFlow: public StatementNode {
public:
    ControlFlow(std::unique_ptr<ConditionNode> condition, std::unique_ptr<AstNode> body);
    std::string toString() override;
protected:
    std::unique_ptr<ConditionNode> condition_;
    std::unique_ptr<AstNode> body_ = nullptr;
};