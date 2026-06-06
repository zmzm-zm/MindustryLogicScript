#include <fstream>
#include <iostream>
#include <stdexcept>
#include <cctype>
#include <frontend/lexer/Token.hpp>
#include <frontend/lexer/Tokenizer.hpp>
#include <frontend/parser/Parser.hpp>
#include <backend/logger/Logger.hpp>


Token::Token(std::string value, Token::Type type): value_(value), type_(type) {}


void Tokenizer::setCurrentFile(const std::string& file) noexcept {
	currentFileName_ = file;
}
void Tokenizer::initializeFile() {
	currentFile_.open(currentFileName_);
	if (!currentFile_.is_open()) {
		throw std::runtime_error("Can not open file \"" + currentFileName_ + "\"");
	}
	contents_ = std::string((std::istreambuf_iterator<char>(currentFile_)),
	std::istreambuf_iterator<char>());
}
bool Tokenizer::isOperator(const std::string& c) noexcept {
	return c == "+" || c == "-" || c == "*" || c == "/" || c == "//" || c == "="
		|| c == "%" || c == "<" || c == ">" || c == "==" || c == "!=" || c == ";";
}
const Token::Type Tokenizer::getToken(std::string value) {
	if (value == "set" ||
		value == "fc" ||
		value == "if" ||
		value == "else" ||
		value == "for") {
		return Token::Type::KEYWORD;
	} else if (isdigit(value[0])) {
		return Token::Type::NUMBER;
	} else if (value[0] == '"') {
		return Token::Type::STRING;
	} else if (isOperator(value)) {
		return Token::Type::OPERATOR;
	} else if (value == ";") {
		return Token::Type::END;
	} else {
		return Token::Type::IDENT;
	}
}
const Token Tokenizer::nextToken() {
    while (pos_ < contents_.size() && isspace(contents_[pos_])) {
    	pos_++;
    }
    if (pos_ >= contents_.size()) return Token("EOF", Token::Type::EOF_);
    // 获取当前位置的字符并递增位置
    char c = contents_[pos_++];
    std::string value = "";
    // 当前位置是运算符时直接返回单个字符
    if (!isOperator(std::string(1, c))) {
    	//否则用这个字符初始化字符串
    	value += c;
    	// 位置不超过文件大小 且 当前位置不是空格或字符 才继续读取
	    while(pos_ < contents_.size()
	    	&& !isspace(contents_[pos_])
	    	&& !isOperator(std::string(1, contents_[pos_]))) {
	        value += contents_[pos_++];
	    }
    } else value = c;
    auto type = getToken(value);
	Logger::instance()->debug("Tokenizer::nextToken(): " + value);
    return Token(value, type);
}
void Tokenizer::pass() {
	// 先到达下一个Token的位置
	while (pos_ < contents_.size() && isspace(contents_[pos_])) {
    	pos_++;
    }
	if (pos_ >= contents_.size()) return;
	char c = contents_[pos_++];
	if (!isOperator(std::string(1, c))) {
	    while(pos_ < contents_.size()
	    	&& !isspace(contents_[pos_])
	    	&& !isOperator(std::string(1, contents_[pos_]))) {
	    	// 不记录字符，直接递增
	        pos_++;
	    }
    }
	Logger::instance()->debug("Tokenizer::pass()");
}
const Token Tokenizer::peek(int offset) {
	// 用局部位置变量代替真实位置
	std::size_t pos = pos_;
	while (pos < contents_.size() && isspace(contents_[pos])) {
    	pos++;
    }
    if (pos >= contents_.size()) return Token("EOF", Token::Type::EOF_);
    char c = contents_[pos++];
    std::string value = "";
    if (!isOperator(std::string(1, c))) {
    	value += c;
	    while(pos < contents_.size()
	    	&& !isspace(contents_[pos])
	    	&& !isOperator(std::string(1, contents_[pos]))) {
	        value += contents_[pos++];
	    }
    } else value = c;    
    auto type = getToken(value);
	Logger::instance()->debug("Tokenizer::peek(): " + value);
    return Token(value, type);
}