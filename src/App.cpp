#include <filesystem>
#include <stdexcept>
#include <iostream>
#include "App.hpp"
#include <frontend/ast/nodes/StatementNode.hpp>
#include <frontend/ast/nodes/AssignmentNode.hpp>
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
	auto currentToken = tokenizer_.peek();
	while(currentToken.type_ != TokenType::EOF_) {
		switch (currentToken.type_) {
			case TokenType::KEYWORD:
				if (currentToken.value_ == "set") {
					auto statement = parser_.parseAssignment();
					ast_.root_->children_.emplace_back(
						new AstNode(std::move(statement))
					);
				}
				break;
			case TokenType::IDENT:
				if (currentToken.value_.find('.') == std::string::npos) {
					auto statement = parser_.parseExpression();
					ast_.root_->children_.emplace_back(
						new AstNode(std::move(statement))
					);
				}
		}
		currentToken = tokenizer_.peek();
	}
	writer_.write(CodeGenerator::generate(ast_.root_));
}
void App::setSourceFiles(int argc, char** argv) {
	for(int i = 1; i < argc; ++i) {
		if (!fs::is_regular_file(argv[i])) {
			throw std::runtime_error(std::string("Can not find file\"") +argv[i] + "\"");
		}
	}
	files_.assign(argv + 1, argv + argc);
}