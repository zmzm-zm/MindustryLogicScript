#pragma once
#include <string>

struct Token {
    enum class Type {
        UNDEFINED,
        KEYWORD,
        IDENT,
        NUMBER,
        STRING,
        OPERATOR,
        END,
        COMMENT,
        EOF_
    };
    std::string value_ = "^v^";
    Type type_ = Type::UNDEFINED;
    Token(std::string value, Type type);
};
