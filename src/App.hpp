#pragma once
#include <string>
#include <vector>
#include <frontend/lexer/Tokenizer.hpp>
#include <frontend/parser/Parser.hpp>
#include <frontend/ast/Ast.hpp>
#include <frontend/ast/nodes/AstNode.hpp>
#include <backend/codegen/CodeGenerator.hpp>
#include <backend/writer/Writer.hpp>
#include <backend/logger/Logger.hpp>
class App {
public:
	App(int argc, char** argv);
	using fileList = std::vector<std::string>;
	void run();
private:
	void setSourceFiles(int argc, char** argv);
	fileList files_;
	Tokenizer tokenizer_;
	Parser parser_;
	Ast ast_;
	Writer writer_;
};