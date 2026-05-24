#pragma once
#include <string>
#include <fstream>
#include <cstddef>
#include "Token.hpp"

class Tokenizer {
public:
	void set_current_file(const std::string& file) noexcept;
	void initialize_file();
	bool is_operator(const std::string& c) noexcept;
	const Token_type get_type(std::string value);
	const Token next_token();
	void pass();
	const Token peek(int offset = 1);
private:
	std::string current_file_name_ = "^v^";
	std::ifstream current_file_;
	std::string contents_ = "^v^";
	std::size_t pos_ = 0;
};