#include <filesystem>
#include <stdexcept>
#include <iostream>
#include <algorithm>
#include "App.hpp"
#include <frontend/ast/nodes/AstNode.hpp>
#include <frontend/ast/nodes/StatementNode.hpp>
#include <backend/logger/Logger.hpp>
#include <frontend/ast/nodes/ExpressionNode.hpp>
#include <frontend/ast/nodes/variable/AssignmentNode.hpp>
namespace fs = std::filesystem;
App::App(int argc, char** argv):
	writer_("output.ml") {
	try {
		setSourceFiles(argc, argv);
	} catch (const std::exception& e) {
		std::cerr << "Error: " << e.what() << std::endl;
	}
	tokenizer_.setCurrentFile(files_[0]);
	tokenizer_.initializeFile();
	parser_.setTokenizer(tokenizer_);
	ast_.root_ = new AstNode(nullptr);
}
void App::run() {
	try {
		processToken();
	} catch (const std::exception& e) {
		std::cerr << "Error: " << e.what() << std::endl;
	}
	writer_.write(CodeGenerator::generate(ast_.root_) + "stop\n");
}

void App::processToken() {
	auto currentToken = tokenizer_.peek();
	while(currentToken.type_ != Token::Type::EOF_) {
		switch (currentToken.type_) {
			case Token::Type::KEYWORD:
				if (currentToken.value_ == "var") variableDeclaration();
				break;
			case Token::Type::IDENT:
				if (currentToken.value_.find("(") == std::string::npos) variableAssignment();
				break;
		}
		currentToken = tokenizer_.peek();
	}
}

void App::variableDeclaration() {
	auto var = tokenizer_.peek(2).value_;
	auto c = tokenizer_.peek(3).value_;
	if (c != "=") Logger::error("expect \"=\"");
	auto it = find(variables_.begin(), variables_.end(), var);
	if (it != variables_.end()) {
		Logger::error("\" " + var + "\" has been declared");
	}
	variables_.emplace_back(var);
	
	auto node = parser_.parseInitialization();
    ast_.root_->children_.emplace_back(
        new AstNode(std::move(node))
    );
}

void App::variableAssignment() {
	auto var = tokenizer_.peek().value_;
	auto c = tokenizer_.peek(2).value_;
	if (c != "=") Logger::error("expect \"=\"");
	auto it = std::find(variables_.begin(), variables_.end(), var);
	if (it == variables_.end()) {
		Logger::error("\" " + var + "\" has not been declared");
	}
	auto node = parser_.parseAssignment();
	ast_.root_->children_.emplace_back(
        new AstNode(std::move(node))
    );
}

void App::setSourceFiles(int argc, char** argv) {
	for(int i = 1; i < argc; ++i) {
		if (!fs::is_regular_file(argv[i])) {
			throw std::runtime_error(std::string("Can not find file\"") +argv[i] + "\"");
		}
	}
	files_.assign(argv + 1, argv + argc);
}
