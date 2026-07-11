#pragma once
#include <vector>
#include <memory>
#include "frontend/ast/nodes/StatementNode.hpp"

class AstNode {
public:
	AstNode();
	AstNode(std::unique_ptr<StatementNode> statementNode);
    std::vector<AstNode*> children_;
    std::unique_ptr<StatementNode> statement_;
};
