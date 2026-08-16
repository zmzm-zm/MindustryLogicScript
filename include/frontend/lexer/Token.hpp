#pragma once
#include <string>

/** @ingroup Lexer
 *  @brief A single lexical token produced by the Tokenizer.
 */
struct Token {
    /// The classification of a token.
    enum class Type {
        UNDEFINED,  ///< Default/unset state.
        KEYWORD,    ///< Language keyword (var, fn, if, while, else, for...).
        IDENT,      ///< Identifier (variable / function name).
        NUMBER,     ///< Numeric literal.
        STRING,     ///< String literal.
        BOOLEAN,    ///< Boolean literal (true / false).
        OPERATOR,   ///< Operator or symbol.
        NONE,       ///< Placeholder for no token.
        END,        ///< Statement terminator (semicolon).
        COMMENT,    ///< Comment marker.
        EOF_        ///< End of file.
    };

    /// The raw text content of the token.
    std::string value_ = "^v^";

    /// The classification of the token.
    Type type_ = Type::UNDEFINED;

    /**
     * @brief Constructs a token with the given text and type.
     * @param value The raw text content of the token.
     * @param type  The classification of the token.
     */
    Token(std::string value, Type type);
};
