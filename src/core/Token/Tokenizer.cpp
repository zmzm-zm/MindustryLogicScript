#include <fstream>
#include <iostream>
#include <stdexcept>
#include <cctype>
#include "Token.hpp"
#include "Tokenizer.hpp"

#include "Parser/Parser.hpp"

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
bool Tokenizer::is_operator(const std::string& c) noexcept {
	return c == "+" || c == "-" || c == "*" || c == "/" || c == "//" || c == "="
		|| c == "%" || c == "<" || c == ">" || c == "==" || c == "!=" || c == ";";
}
const Token_type Tokenizer::get_type(std::string value) {
	if (value == "set" ||
		value == "fc" ||
		value == "if" ||
		value == "else" ||
		value == "for") {
		return Token_type::KEYWORD;
	} else if (isdigit(value[0])) {
		return Token_type::NUMBER;
	} else if (value[0] == '"') {
		return Token_type::STRING;
	} else if (is_operator(value)) {
		return Token_type::OPERATOR;
	} else if (value == ";") {
		return Token_type::END;
	} else {
		return Token_type::IDENT;
	}
}
const Token Tokenizer::next_token() {
    while (pos_ < contents_.size() && isspace(contents_[pos_])) {
    	pos_++;
    }
    if (pos_ >= contents_.size()) return Token("EOF", Token_type::EOF_);
    char c = contents_[pos_++];
    std::string value = "";
    if (!is_operator(std::string(1, c))) {
    	value += c;
	    while(pos_ < contents_.size()
	    	&& !isspace(contents_[pos_])
	    	&& !is_operator(std::string(1, contents_[pos_]))) {
	        value += contents_[pos_++];
	    }
    } else value = c;
    // 添加调试
    std::cout << "next_token: read '" << value << "' at pos " << pos_ << std::endl;
    
    auto type = get_type(value);
    return Token(value, type);
}
void Tokenizer::pass() {
	while (pos_ < contents_.size() && isspace(contents_[pos_])) {
    	pos_++;
    }
	if (pos_ >= contents_.size()) return;
	char c = contents_[pos_++];
	if (!is_operator(std::string(1, c))) {
	    while(pos_ < contents_.size()
	    	&& !isspace(contents_[pos_])
	    	&& !is_operator(std::string(1, contents_[pos_]))) {
	        contents_[pos_++];
	    }
    }
}
const Token Tokenizer::peek(int offset) {
	std::size_t pos = pos_;
	while (pos < contents_.size() && isspace(contents_[pos])) {
    	pos++;
    }
    if (pos >= contents_.size()) return Token("EOF", Token_type::EOF_);
    char c = contents_[pos++];
    std::string value = "";
    if (!is_operator(std::string(1, c))) {
    	value += c;
	    while(pos < contents_.size()
	    	&& !isspace(contents_[pos])
	    	&& !is_operator(std::string(1, contents_[pos]))) {
	        value += contents_[pos++];
	    }
    } else value = c;
    // 添加调试
    std::cout << "peek: read '" << value << "' at pos " << pos << std::endl;
    
    auto type = get_type(value);
    return Token(value, type);
}