#include <fstream>
#include <stdexcept>
#include <cctype>
#include "Token.hpp"
#include "Tokenizer.hpp"

#include "../Parser/Parser.hpp"

Token::Token(std::string value, Token_type type): value_(value), type_(type) {}


void Tokenizer::set_current_file(const std::string& file) noexcept {
	current_file_name_ = file;
}
void Tokenizer::initialize_file() {
	current_file_.open(current_file_name_);
	if (!current_file_.is_open()) {
		throw std::runtime_error("Can not open file \"" + current_file_name_ + "\"");
	}
	contents_ = std::string((std::istreambuf_iterator<char>(current_file_)),
	std::istreambuf_iterator<char>());
}
bool Tokenizer::is_operator(const char& c) noexcept {
	return c == '+' || c == '-' || c == '*' || c == '/' || c == '=' || c == '(' || c == ')'
		|| c == '%' || c == '<' || c == '>' || c == '\\' || c == '"' || c == '\'';
}
const Token Tokenizer::next_token() {
	char c = contents_[pos_++];
	std::string value;
	while(pos_ < contents_.size() && !isspace(c)) {
		value += c;
		c = contents_[pos_++];
	}
	Token_type type;
	if (value == "set" ||
		value == "fc" ||
		value == "if" ||
		value == "else" ||
		value == "for") {
		type = Token_type::KEYWORD;
	} else if (isdigit(value[0])) {
		type = Token_type::NUMBER;
	} else if (value[0] == '"') {
		type = Token_type::STRING;
	} else if (value.size() == 1 && is_operator(value[0])) {
		type = Token_type::OPERATOR;
	} else {
		type = Token_type::IDENT;
	}
	return Token(value, type);
}
void Tokenizer::pass() {
	while(pos_ < contents_.size() && !isspace(contents_[pos_++])) {}
	pos_--;
}
