#include <filesystem>
#include <memory>
#include <stdexcept>
#include <iostream>
#include <algorithm>
#include "App.hpp"
#include <frontend/ast/nodes/AstNode.hpp>
#include <frontend/ast/nodes/StatementNode.hpp>
#include <backend/logger/Logger.hpp>
#include <backend/codegen/CodeGenerator.hpp>
#include <frontend/lexer/Token.hpp>
namespace fs = std::filesystem;
App::App(const uint8_t argc, char** argv):
	writer_(argv[1] + std::string(".ml")) {
	try {
		setSourceFiles(argc, argv);
	} catch (const std::exception& e) {
		std::cerr << "Error: " << e.what() << std::endl;
	}
	tokenizer_.setCurrentFile(files_[0]);
	tokenizer_.initializeFile();
	parser_.setTokenizer(tokenizer_);
	root_ = new AstNode(nullptr);
}

void App::setSourceFiles(const uint8_t argc, char** argv) {
	for(uint8_t i = 2; i < argc; ++i) {
		if (!fs::is_regular_file(argv[i])) {
			throw std::runtime_error(std::string("Can not find file\"") +argv[i] + "\"");
		}
	}
	files_.assign(argv + 2, argv + argc);
}

void App::run() {
	try {
		processToken();
	} catch (const std::exception& e) {
		std::cerr << "Error: " << e.what() << std::endl;
	}
	writer_.write(CodeGenerator::generate(root_) + "stop\n");
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
			default:
				throw std::runtime_error("Unexpected token type");
		}
		currentToken = tokenizer_.peek();
	}
}

void App::variableDeclaration() {
	auto var = tokenizer_.peek(2).value_;
	auto c = tokenizer_.peek(3).value_; 
	if (c != "=" && c != ";") Logger::error("expect \"=\" or \";\"");
	auto it = std::ranges::find(variables_, var);
	if (it != variables_.end()) {
		Logger::error("\" " + var + "\" has been declared");
	}
	variables_.emplace_back(var);
	std::unique_ptr<StatementNode> node;
	if(c == ";") node = parser_.parseDeclaration();
	else node = parser_.parseInitialization();
    root_->children_.emplace_back(
        new AstNode(std::move(node))
    );
}

void App::variableAssignment() {
	auto var = tokenizer_.peek().value_;
	auto c = tokenizer_.peek(2).value_;
	if (c != "=") Logger::error("expect \"=\"");
	auto it = std::ranges::find(variables_, var);
	if (it == variables_.end()) {
		Logger::error("\" " + var + "\" has not been declared");
	}
	auto node = parser_.parseAssignment();
	root_->children_.emplace_back(
        new AstNode(std::move(node))
    );
}
