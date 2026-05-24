#pragma once
#include <string>
#include <vector>
#include "Token/Tokenizer.hpp"
#include "Parser/Parser.hpp"
#include "AST/Ast.hpp"
#include "AST/Ast_node.hpp"
#include "Writer/Code_generator.hpp"
#include "Writer/Writer.hpp"
class App {
public:
	App(int argc, char** argv);
	using file_list = std::vector<std::string>;
	void run();
private:
	void set_source_files(int argc, char** argv);
	file_list files_;
	Tokenizer tokenizer_;
	Parser parser_;
	AST ast_;
	Writer writer_;
};