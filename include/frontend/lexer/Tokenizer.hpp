#pragma once
#include <string>
#include <fstream>
#include <cstddef>
#include <cstdint>
#include <frontend/lexer/Token.hpp>

/**
 * @defgroup Frontend Frontend
 * @ingroup Core
 * @brief Input-side modules: lexical analysis, parsing and the AST.
 */

/**
 * @defgroup Lexer Lexer
 * @ingroup Frontend
 * @brief Lexical analysis: splits the source text into tokens.
 */

/** @ingroup Lexer
 *  @brief The precedence level of an arithmetic operator.
 */
enum class OperatorType {
    Multiplication = 2, ///< Precedence 2.
    Division = 2,       ///< Precedence 2.
    Addition = 1,       ///< Precedence 1.
    Subtraction = 1,    ///< Precedence 1.
    Undefined = 999999, ///< No operator.
};

/** @ingroup Lexer
 *  @brief Splits the source text into a stream of Tokens.
 */
class Tokenizer {
	enum class Strategy;
public:
    /**
     * @brief Maps an arithmetic operator symbol to its OperatorType.
     * @param operator_ The operator symbol (+, -, *, /).
     * @return The corresponding OperatorType.
     */
    static OperatorType analyzeOperator(std::string_view operator_) noexcept;

    /**
     * @brief Sets the current source file and resets internal state.
     * @param file The path of the source file to process.
     */
    void setCurrentFile(std::string file) noexcept;

    /** @brief Opens the current file and loads its full contents into memory. */
    void initializeFile();

    /** @brief Resets the tokenizer to its default empty state. */
    void reset() noexcept;

    /**
     * @brief Checks whether the given character is an operator.
     * @param c The character to test.
     * @return True if it is an operator.
     */
    static bool isOperator(std::string_view c) noexcept;

    /**
     * @brief Classifies a token's text into a Token::Type.
     * @param value The token text.
     * @return The inferred token type.
     */
    static Token::Type getToken(std::string_view value);

    /**
     * @defgroup TokenGetter Token getters
     * @ingroup Lexer
     * @brief Functions that fetch tokens in different modes.
     */
    /**
     * @addtogroup TokenGetter
     * @{
     */
    /**
     * @brief Base function for reading a token.
     * @details Merges the duplicated logic shared by nextToken, pass and peek.
     */
    Token readToken(Strategy strategy, uint8_t offset = 1);

    /**
     * @brief Reads and returns the next token.
     * @return A constant token.
     * @note This advances the current position in the file.
     */
    Token nextToken();

    /**
     * @brief Skips the next token.
     * @note This advances the current position in the file.
     */
    void pass();

    /**
     * @brief Looks ahead n tokens without consuming them.
     * @param offset Which token ahead to look at (default 1).
     * @return A constant token.
     * @note This does not advance the current position in the file.
     */
    Token peek(const uint8_t offset = 1);
    /** @} */

private:
    /// The read strategy controlling whether the position advances.
    enum class Strategy {
        CONSUMPTIVE,    ///< Advances the position.
        NON_CONSUMPTIVE,///< Does not advance the position.
        NO_RETURN       ///< Consumes without returning a token.
    };

    std::string currentFileName_ = "^v^"; ///< Path of the current source file.
    std::ifstream currentFile_;            ///< File stream for reading the source.
    std::string contents_ = "^v^";        ///< Full source text loaded into memory.
    std::size_t pos_ = 0;                  ///< Current read position.
};
