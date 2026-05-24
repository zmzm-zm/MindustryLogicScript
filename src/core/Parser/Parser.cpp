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
}