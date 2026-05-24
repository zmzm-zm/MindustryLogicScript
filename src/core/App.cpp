#include <filesystem>
#include <stdexcept>
#include <iostream>
#include "App.hpp"
#include "Statement/Statement.hpp"
#include "Statement/Assignment_statement.hpp"
namespace fs = std::filesystem;
App::App(int argc, char** argv):
	writer_("output.ml") {
	try {
		set_source_files(argc, argv);
	} catch (const std::exception& e) {
		std::cerr << "Error: " << e.what() << std::endl;
	}
	tokenizer_.set_current_file(files_[0]);
	tokenizer_.initialize_file();
	parser_.set_tokenizer(tokenizer_);
	ast_.root_ = new AST_node(nullptr);
}
void App::run() {
	auto current_token = tokenizer_.peek();
	while(current_token.type_ != Token_type::EOF_) {
		switch (current_token.type_) {
			case Token_type::KEYWORD:
				if (current_token.value_ == "set") {
					auto statement = parser_.parse_assignment();
					ast_.root_->children_.emplace_back(
						new AST_node(
							std::move(statement)
							/*
							std::make_unique<Assignment_statement>(
								statement->get_variable(),
								statement->get_value()
							)
							*/
						)
					);
				}
				break;
			case Token_type::IDENT:
				if (current_token.value_.find('.') == std::string::npos) {
					auto statement = parser_.parse_expression();
					ast_.root_->children_.emplace_back(
						new AST_node(
							std::move(statement)
						)
					);
				}
		}
		current_token = tokenizer_.peek();
	}
	writer_.write(Code_generator::generate(ast_.root_));
}
void App::set_source_files(int argc, char** argv) {
	for(int i = 1; i < argc; ++i) {
		if (!fs::is_regular_file(argv[i])) {
			throw std::runtime_error(std::string("Can not find file\"") +argv[i] + "\"");
		}
	}
	files_.assign(argv + 1, argv + argc);
}