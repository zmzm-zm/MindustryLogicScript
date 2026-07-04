#pragma once
#include <string>
#include <frontend/ast/nodes/variable/VariableNode.hpp>
class DeclarationNode final: public VariableNode {
public:
	explicit DeclarationNode(std::string variable);
	std::string toString() override;
	std::string getVar() const override;
};
