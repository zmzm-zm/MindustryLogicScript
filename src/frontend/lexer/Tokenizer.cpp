#include <fstream>
#include <iostream>
#include <stdexcept>
#include <cctype>
#include <frontend/lexer/Token.hpp>
#include <frontend/lexer/Tokenizer.hpp>
#include <backend/logger/Logger.hpp>
#include <utility>


Token::Token(std::string value, Token::Type type): value_(std::move(value)), type_(type) {}

OperatorType Tokenizer::analyzeOperator(std::string_view operator_) noexcept {
	if (operator_ == "*") return OperatorType::Multiplication;
	if (operator_ == "/") return OperatorType::Division;
	if (operator_ == "+") return OperatorType::Addition;
	if (operator_ == "-") return OperatorType::Subtraction;
	return OperatorType::Undefined;
}
void Tokenizer::setCurrentFile(std::string file) noexcept {
	currentFileName_ = std::move(file);
}
void Tokenizer::initializeFile() {
	currentFile_.open(currentFileName_);
	if (!currentFile_.is_open()) {
		throw std::runtime_error("Can not open file \"" + currentFileName_ + "\"");
	}
	contents_ = std::string((std::istreambuf_iterator<char>(currentFile_)),
	std::istreambuf_iterator<char>());
}
bool Tokenizer::isOperator(std::string_view c) noexcept {
	return c == "+" || c == "-" || c == "*" || c == "/" || c == "//" || c == "="
		|| c == "%" || c == "<" || c == ">" || c == "==" || c == "!=" || c == ";"
		|| c == "&&" || c == "||" || c == "(" || c == ")" || c == "{" || c == "}"
		|| c == "!=" || c == "<=" || c == ">=";
}
Token::Type Tokenizer::getToken(const std::string_view value) {
	if (value == "var" ||
		value == "fn" ||
		value == "if" ||
		value == "while" ||
		value == "else" ||
		value == ":" ||
		value == "for") return Token::Type::KEYWORD;
	if (isdigit(value[0])) return Token::Type::NUMBER;
	if (value[0] == '"') return Token::Type::STRING;
	if (isOperator(value)) return Token::Type::OPERATOR;
	if (value == ";") return Token::Type::END;
	if (value == "~") return Token::Type::COMMENT;
	return Token::Type::IDENT;
}
Token Tokenizer::readToken(const Strategy strategy, const uint8_t offset) {
	std::size_t posCopy = pos_;
	std::size_t* pos;
	if (strategy == Strategy::NON_CONSUMPTIVE) {
		pos = &posCopy;
	} else {
		pos = &pos_;
	}
	std::string value;
	Token::Type type = Token::Type::UNDEFINED;
	for (uint8_t i = 0; i < offset; ++i) {
		while (*pos < contents_.size()) {
			if (isspace(contents_[*pos])) {
				(*pos)++;
			} else if (*pos + 1 < contents_.size()
						&& contents_[*pos] == '~'
						&& contents_[*pos + 1] == '~') {
				(*pos) += 2;
				while (*pos + 1 < contents_.size()
					&& !(contents_[*pos] == '~' && contents_[*pos + 1] == '~')) {
					(*pos)++;
				}
				if (*pos + 1 < contents_.size()) {
					(*pos) += 2; // 跳过结束 ~~
				}
			} else if (contents_[*pos] == '~') {
				(*pos)++;
				while (*pos < contents_.size()
					   && contents_[*pos] != '\n'
					   && contents_[*pos] != '~') {
					(*pos)++;
					   }
				if (*pos < contents_.size()) (*pos)++;
			} else {
				break;
			}
		}
		if (*pos >= contents_.size()) return {"EOF", Token::Type::EOF_};
		std::string c;
		c = contents_[(*pos)++];
		if (c == "&" && contents_[*pos] == '&'
			|| c == "=" && contents_[*pos] == '='
			|| c == "|" && contents_[*pos] == '|'
			|| c == "!" && contents_[*pos] == '='
			|| c == "<" && contents_[*pos] == '='
			|| c == ">" && contents_[*pos] == '=') {
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
	return {value, type};
}

Token Tokenizer::next(std::string name, int line) {
	auto token = readToken(Strategy::CONSUMPTIVE);
	if (token.value_ != "EOF") Logger::instance()->debug(name + "-" + std::to_string(line) + "-next: " + token.value_);
	return token;

}
void Tokenizer::pass() {
	const auto token = readToken(Strategy::CONSUMPTIVE);
	Logger::instance()->debug(std::to_string(pos_) + "-pass: " + token.value_);

}

Token Tokenizer::peek(const uint8_t offset) {
	auto token = readToken(Strategy::NON_CONSUMPTIVE, offset);
	Logger::instance()->debug(std::to_string(pos_) + "-peek: " + token.value_);
    return token;

}