#pragma once
#include <string>
#include <frontend/ast/nodes/variable/VariableNode.hpp>
class AssignmentNode final: public VariableNode {
public:
	AssignmentNode(std::string variable, std::unique_ptr<ExpressionNode> value);
	std::string toString() override;
};
