#include "Ast_node.hpp"
AST_node::AST_node(std::unique_ptr<Statement> statement) {
	statement_ = std::move(statement);
}