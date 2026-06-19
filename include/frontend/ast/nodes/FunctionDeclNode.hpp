#pragma once
#include <frontend/ast/nodes/StatementNode.hpp>
#include <string>
class FunctionDeclNode : public StatementNode {
public:
	FunctionDeclNode();
	std::string toString() override;
private:

};
