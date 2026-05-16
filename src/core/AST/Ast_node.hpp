#pragma once
#include <vector>
#include "memory"
#include "Statement/Statement.hpp"

class AST_node {
private:
    std::pmr::vector<std::unique_ptr<AST_node>> children_;
    std::unique_ptr<Statement> statement_;
};
