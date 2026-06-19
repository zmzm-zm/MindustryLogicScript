#pragma once
#include <string>
#include <memory>
#include <frontend/ast/nodes/StatementNode.hpp>
#include <frontend/ast/nodes/ExpressionNode.hpp>
class VariableNode : public StatementNode {
public:
	VariableNode(const std::string& variable, std::unique_ptr<ExpressionNode> value);
	virtual std::string getVar() const;
protected:
	std::string variable_ = "^v^";
	std::unique_ptr<ExpressionNode> value_;
};
