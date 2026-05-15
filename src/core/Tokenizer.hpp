#pragma once
#include <string>
#include <fstream>
#include <cstddef>
enum class Token_type {
	UNDEFINED,
	KEYWORD,
	IDENT,
	NUMBER,
	STRING,
	OPERATOR,
	END
};
struct Token {
	std::string value_ = "^v^";
	Token_type type_ = Token_type::UNDEFINED;
	Token(std::string value, Token_type type);
};
class Tokenizer {
public:
	void set_current_file(const std::string& file) noexcept;
	void initialize_file();
	const Token next_token();
private:
	std::string current_file_name_ = "^v^";
	std::ifstream current_file_;
	std::string contents_ = "^v^";
	std::size_t pos_;
};