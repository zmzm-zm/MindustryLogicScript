#pragma once
#include <string>
#include <frontend/ast/nodes/variable/VariableNode.hpp>
class AssignmentNode : public VariableNode {
public:
	AssignmentNode(const std::string& variable, std::unique_ptr<ExpressionNode> value);
	std::string toString() override;
};
