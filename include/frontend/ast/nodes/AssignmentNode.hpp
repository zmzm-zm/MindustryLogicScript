#pragma once
#include <string>
#include <memory>
#include <frontend/ast/nodes/StatementNode.hpp>
class ExpressionNode;

class AssignmentNode : public StatementNode {
public:
    AssignmentNode(const std::string& variable, std::unique_ptr<ExpressionNode> value);
    std::string toString() override;
    std::string getVar() const;
private:
    std::string variable_ = "^v^";
    std::unique_ptr<ExpressionNode> value_;
};