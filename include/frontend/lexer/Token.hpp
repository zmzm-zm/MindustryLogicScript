#pragma once
#include <string>

enum class TokenType {
    UNDEFINED,
    KEYWORD,
    IDENT,
    NUMBER,
    STRING,
    OPERATOR,
    END,
    EOF_
};
struct Token {
    std::string value_ = "^v^";
    TokenType type_ = TokenType::UNDEFINED;
    Token(std::string value, TokenType type);
};