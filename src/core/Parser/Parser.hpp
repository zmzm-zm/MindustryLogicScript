#pragma once
#include <memory>

#include "Statement/Statement.hpp"
#include "Token/Tokenizer.hpp"

class Parser {
public:
    void set_tokenizer(Tokenizer& tokenizer);
    std::unique_ptr<Statement> parse_assignment() const;
private:
    Tokenizer* tokenizer_ = nullptr;
};
