#include <filesystem>
#include <stdexcept>
#include <iostream>
#include "App.hpp"
#include <frontend/ast/nodes/StatementNode.hpp>
#include <frontend/ast/nodes/AssignmentNode.hpp>
#include <backend/logger/Logger.hpp>
#include <frontend/ast/nodes/ExpressionNode.hpp>
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
	while(currentToken.type_ != Token::Type::EOF_) {
		switch (currentToken.type_) {
			case Token::Type::KEYWORD:
				if (currentToken.value_ == "set") {
					/*
				    std::string var; 
				    try {
				        var = variableDeclaration();
				    } catch (const std::exception& e) {
				        std::cerr << "Error: " << e.what() << std::endl;
				        Logger::instance()->error(e.what());
				    }
				    // 1. parseExpression 不需要传 var，它返回的是表达式树
				    auto node = parser_.parseExpression(var);
				    
				    // 2. AssignmentNode 需要 unique_ptr，所以用 std::move
				    // 3. node.get() 改成 std::move(node)
				    */
				    auto node = parser_.parseAssignment();
				    ast_.root_->children_.emplace_back(
				        new AstNode(std::move(node))
				    );
				}
				break;
			case Token::Type::IDENT:
			/*
				if (currentToken.value_.find('(') != std::string::npos) {
					
				} else {
					auto statement = parser_.parseExpression();
					ast_.root_->children_.emplace_back(
						new AstNode(std::move(statement))
					);
				}*/
		}
		currentToken = tokenizer_.peek();
	}
	writer_.write(CodeGenerator::generate(ast_.root_) + "stop\n");
}
void App::setSourceFiles(int argc, char** argv) {
	for(int i = 1; i < argc; ++i) {
		if (!fs::is_regular_file(argv[i])) {
			throw std::runtime_error(std::string("Can not find file\"") +argv[i] + "\"");
		}
	}
	files_.assign(argv + 1, argv + argc);
}

const std::string& App::variableDeclaration() {
	tokenizer_.pass();
	auto var = tokenizer_.nextToken().value_;
	auto c = tokenizer_.nextToken().value_;
	if (c != "=") throw std::runtime_error("expect \"=\"");
	variables_.emplace_back(var);
	return std::string(var);
}