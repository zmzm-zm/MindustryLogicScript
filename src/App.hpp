#pragma once
#include <string>
#include <vector>
#include <frontend/lexer/Tokenizer.hpp>
#include <frontend/parser/Parser.hpp>
#include <backend/writer/Writer.hpp>
#include <backend/logger/Logger.hpp>
#include <frontend/ast/nodes/AstNode.hpp>
class App {
public:
	App(uint8_t argc, char** argv);
	using fileList = std::vector<std::string>;
	void run();
private:
	void variableDeclaration();
	void variableAssignment();
	void processToken();
	void setSourceFiles(uint8_t argc, char** argv);
	fileList files_;
	Parser parser_;
	AstNode* root_;
	Tokenizer tokenizer_;
	Writer writer_;
	std::vector<std::string> variables_;
};
