#pragma once
#include <string>
#include <frontend/ast/nodes/variable/VariableNode.hpp>

class InitializationNode final: public VariableNode {
public:
	InitializationNode(std::string variable, std::unique_ptr<ExpressionNode> value);
    std::string toString() override;
};
