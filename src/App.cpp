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
}
App::~App() {}

void App::setSourceFiles(const uint8_t argc, char** argv) {
	for(uint8_t i = 2; i < argc; ++i) {
		if (!fs::is_regular_file(argv[i])) {
			throw std::runtime_error(std::string("Can not find file\"") +argv[i] + "\"");
		}
	}
	files_.assign(argv + 2, argv + argc);
}

void App::run() {
	auto root = std::make_unique<AstNode>();
	parser_.setRoot(std::move(root));
	try {
		parser_.process();
	} catch (const std::exception& e) {
		std::cerr << "Error: " << e.what() << std::endl;
	}
	root = parser_.getRoot();
	writer_.write(CodeGenerator::generate(root.get()) + "stop\n");
}


