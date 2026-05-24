#include <vector>
#include "Token/Token.hpp"
#include "Parser.hpp"
#include "Statement/Statement.hpp"
#include "Statement/Assignment_statement.hpp"
#include "Statement/Operation_statement.hpp"

void Parser::set_tokenizer(Tokenizer& tokenizer) {
    tokenizer_ = &tokenizer;
}
std::unique_ptr<Assignment_statement> Parser::parse_assignment() const {
	tokenizer_->pass();
    auto variable = tokenizer_->next_token();
    tokenizer_->pass();
    auto value = tokenizer_->next_token();
    tokenizer_->pass();
    return std::make_unique<Assignment_statement>(variable.value_, value.value_);
}
std::unique_ptr<Operation_statement> Parser::parse_expression() const {
	std::string left = tokenizer_->next_token().value_;
	std::string operator__ = tokenizer_->next_token().value_;
	if (operator__ == ";") return std::make_unique<Operation_statement>(left, operator__, nullptr);
	return std::make_unique<Operation_statement>(left, operator__, parse_expression());
	/*
	std::string a = tokenizer_->next_token().value_;
	if (a == ";") return nullptr;
	std::string operator_ = tokenizer_->next_token().value_;
	if (operator_ == ";") return nullptr;
	return std::make_unique<Operation_statement>(a, parse_expression(), operator_);
	*/
	/*
	std::vector<std::string> tokens;
	Operator_type type;
	std::string a, b, operator_;
	auto current_token = tokenizer_->next_token();
	int index = 0;
	while (current_token.value_ != ";") {
		tokens.push_back(current_token.value_);
		if (size >= 2) {
			b += tokens[index];
		} 
		current_token = tokenizer_->next_token();
		++index;
	}
	a = tokens[0];
	operator_ = tokens[1];
	if (operator_ == "*") {
		type = Operator_type::Multiplication;
	} else if (operator_ == "/") {
		type = Operator_type::Division;
	} else if (operator_ == "+") {
		type = Operator_type::Addition;
	} else if (operator_ == "-") {
		type = Operator_type::Subtraction;
	}
	
	return std::make_unique<Operation_statement>(a, b, type);
	*/
}