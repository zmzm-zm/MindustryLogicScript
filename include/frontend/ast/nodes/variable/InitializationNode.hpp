#pragma once
#include <string>
#include <frontend/ast/nodes/variable/VariableNode.hpp>

class InitializationNode : public VariableNode {
public:
	InitializationNode(const std::string& variable, std::unique_ptr<ExpressionNode> value);
    std::string toString() override;
};
