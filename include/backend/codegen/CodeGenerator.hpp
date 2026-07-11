#pragma once
#include <string>
#include <frontend/ast/nodes/AstNode.hpp>
class CodeGenerator {
public:
	static std::string generate(const AstNode* node);
};