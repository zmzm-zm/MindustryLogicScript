#pragma once
#include <string>
#include "AST/Ast.hpp"
class Code_generator {
public:
	static std::string generate(const AST_node* node);
private:
};