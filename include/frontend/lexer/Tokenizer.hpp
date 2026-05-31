#pragma once
#include <string>
#include <fstream>
#include <cstddef>
#include <frontend/lexer/Token.hpp>

class Tokenizer {
public:
	void setCurrentFile(const std::string& file) noexcept;
	void initializeFile();
	bool isOperator(const std::string& c) noexcept;
	const TokenType getType(std::string value);
	const Token nextToken();
	void pass();
	const Token peek(int offset = 1);
private:
	std::string currentFileName_ = "^v^";
	std::ifstream currentFile_;
	std::string contents_ = "^v^";
	std::size_t pos_ = 0;
};