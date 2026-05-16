#include "Parser.hpp"

#include "Statement/Assignment_statement.hpp"

void Parser::set_tokenizer(Tokenizer& tokenizer) {
    tokenizer_ = &tokenizer;
}
std::unique_ptr<Statement> Parser::parse_assignment() const {
    auto variable = tokenizer_->next_token();
    tokenizer_->pass();
    auto value = tokenizer_->next_token();
    return std::make_unique<Assignment_statement>(variable.value_, value.value_);
}
