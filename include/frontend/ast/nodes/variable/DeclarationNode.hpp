#pragma once
#include <string>
#include <frontend/ast/nodes/variable/VariableNode.hpp>
class DeclarationNode :public VariableNode {
public:
	DeclarationNode(const std::string& variable);
	std::string toString() override;
	std::string getVar() const override;
};
