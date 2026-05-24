#pragma once
#include <string>

enum class Token_type {
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
    Token_type type_ = Token_type::UNDEFINED;
    Token(std::string value, Token_type type);
};