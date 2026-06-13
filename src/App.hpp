#pragma once
#include <string>
#include <vector>
#include <frontend/lexer/Token.hpp>
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
	void variableDeclaration();
	void variableAssignment();
	void processToken();
	void error(std::string msg);
	void setSourceFiles(int argc, char** argv);
	fileList files_;
	Parser parser_;
	Ast ast_;
	Tokenizer tokenizer_;
	Writer writer_;
	std::vector<std::string> variables_;
};
