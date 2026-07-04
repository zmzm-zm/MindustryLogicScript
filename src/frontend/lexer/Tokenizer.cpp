#include <fstream>
#include <iostream>
#include <stdexcept>
#include <cctype>
#include <frontend/lexer/Token.hpp>
#include <frontend/lexer/Tokenizer.hpp>
#include <frontend/parser/Parser.hpp>
#include <backend/logger/Logger.hpp>


Token::Token(std::string value, Token::Type type): value_(value), type_(type) {}

OperatorType Tokenizer::analyzeOperator(const std::string& operator__) {
	if (operator__ == "*") return OperatorType::Multiplication;
	else if (operator__ == "/") return OperatorType::Division;
	else if (operator__ == "+") return OperatorType::Addition;
	else if (operator__ == "-") return OperatorType::Subtraction;
	else return OperatorType::Undefined;
}
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
		|| c == "%" || c == "<" || c == ">" || c == "==" || c == "!=" || c == ";"
		|| c == "&&";
}
const Token::Type Tokenizer::getToken(std::string value) {
	if (value == "var" ||
		value == "fn" ||
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
const Token Tokenizer::readToken(Strategy strategy, uint8_t offset) {
	std::size_t posCopy = pos_;
	std::size_t* pos;
	if (strategy == Strategy::NON_CONSUMPTIVE) {
		pos = &posCopy;
	} else {
		pos = &pos_;
	}
	std::string value = "";
	Token::Type type;
	for (int i = 0; i < offset; ++i) {
		while (*pos < contents_.size() && isspace(contents_[*pos])) {
			(*pos)++;
		}
		if (*pos >= contents_.size()) return Token("EOF", Token::Type::EOF_);
		std::string c;
		c = contents_[(*pos)++];
		if (c == "&" && contents_[*pos] == '&') {
			c += contents_[(*pos)++];
		}
		value = "";
		if (!isOperator(c)) {
			value += c;
			while(*pos < contents_.size()
				&& !isspace(contents_[*pos])
				&& !isOperator(std::string(1, contents_[*pos]))) {
				value += contents_[(*pos)++];
				}
		} else value = c;
		type = getToken(value);
	}
	return Token(value, type);
}


const Token Tokenizer::nextToken() {
	auto token = readToken(Strategy::CONSUMPTIVE);
	Logger::instance()->debug("Tokenizer::nextToken(): " + token.value_);
	return token;

}
void Tokenizer::pass() {
	auto token = readToken(Strategy::CONSUMPTIVE);
	Logger::instance()->debug("Tokenizer::pass(): " + token.value_);

}
const Token Tokenizer::peek(uint8_t offset) {
	auto token = readToken(Strategy::NON_CONSUMPTIVE, offset);
	Logger::instance()->debug("Tokenizer::peek(): " + token.value_);
    return token;

}