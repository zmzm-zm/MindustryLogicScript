#pragma once
#include <string>
#include <frontend/ast/Ast.hpp>
class CodeGenerator {
public:
	static std::string generate(const AstNode* node);
};