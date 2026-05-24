#pragma once
#include <memory>
#include "Statement/Statement.hpp"
#include "Statement/Operation_statement.hpp"
#include "Statement/Assignment_statement.hpp"
#include "Token/Token.hpp"
#include "Token/Tokenizer.hpp"


class Parser {
public:
    void set_tokenizer(Tokenizer& tokenizer);
    std::unique_ptr<Assignment_statement> parse_assignment() const;
    std::unique_ptr<Operation_statement> parse_expression() const;
private:
    Tokenizer* tokenizer_ = nullptr;
};
