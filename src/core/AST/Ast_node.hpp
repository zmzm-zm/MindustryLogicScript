#pragma once
#include <vector>
#include <memory>
#include "Statement/Statement.hpp"

class AST_node {
public:
	AST_node(std::unique_ptr<Statement> statement);
    std::vector<AST_node*> children_;
    std::unique_ptr<Statement> statement_;
};
