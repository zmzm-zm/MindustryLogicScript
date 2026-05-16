#pragma once
#include <string>
#include <fstream>
#include <cstddef>
#include "Token.hpp"

class Tokenizer {
public:
	void set_current_file(const std::string& file) noexcept;
	void initialize_file();
	bool is_operator(const char& c) noexcept;
	const Token next_token();
	void pass();
private:
	std::string current_file_name_ = "^v^";
	std::ifstream current_file_;
	std::string contents_ = "^v^";
	std::size_t pos_ = 0;
};