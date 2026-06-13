#pragma once
#include <memory>
#include <string>
#include <frontend/ast/nodes/StatementNode.hpp>
#include <frontend/ast/nodes/ExpressionNode.hpp>
class AssignmentNode : public StatementNode {
public:
	AssignmentNode(std::string variable, std::unique_ptr<ExpressionNode> value);
	std::string toString() override;
private:
	std::string variable_ = "huh";
	std::unique_ptr<ExpressionNode> value_;
};
