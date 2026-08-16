#pragma once
#include <frontend/ast/nodes/StatementNode.hpp>
#include <memory>
#include <stack>
#include <string>
#include <frontend/ast/nodes/AstNode.hpp>
#include <spdlog/logger.h>
class VariableNode;
class AstNode;
class ControlFlow;
class Tokenizer;
class InitializationNode;
class AssignmentNode;
class OperationNode;
class DeclarationNode;
class ConditionNode;
enum class OperatorType;

/**
 * @defgroup Parser Parser
 * @ingroup Frontend
 * @brief Recursive-descent parser that builds the AST from the token stream.
 */

/** @ingroup Parser
 *  @brief Recursive-descent parser that builds the AST from the token stream.
 */
class Parser {
public:
    /// @brief Constructs a parser.
    Parser();
    /// @brief Destroys the parser.
    ~Parser();

    /**
     * @brief Pushes a new root node onto the parser's stack.
     * @param root The root AST node to set.
     */
    void setRoot(std::unique_ptr<AstNode> root);

    /**
     * @brief Pops and returns the topmost root node.
     * @return The current root AST node.
     */
    std::unique_ptr<AstNode> getRoot();

    /** @brief Parses the token stream into the AST until end of input. */
    void process();

    /**
     * @brief Binds the tokenizer used by the parser.
     * @param tokenizer The tokenizer to read tokens from.
     */
    void setTokenizer(Tokenizer& tokenizer);

private:
    /**
     * @brief Parses a variable declaration (var x;).
     * @return The declaration node.
     */
    std::unique_ptr<VariableNode> parseDeclaration();

    /**
     * @brief Parses a variable initialization (var x = expr;).
     * @return The initialization node.
     */
    std::unique_ptr<VariableNode> parseInitialization();

    /**
     * @brief Parses a variable assignment (x = expr;).
     * @return The assignment node.
     */
    std::unique_ptr<VariableNode> parseAssignment() const;

    /**
     * @brief Parses an arithmetic operation expression using operator precedence.
     * @param name  The base name for generated result variables.
     * @param index Starting index for generated result names.
     * @return The root operation node.
     */
    std::unique_ptr<OperationNode> parseOperation(
        std::string name = "^v^",
        std::size_t index = 0) const;

    /**
     * @brief Parses a boolean condition ending at the given token.
     * @param ending The token value that terminates the condition.
     * @return The condition node.
     */
    std::unique_ptr<ConditionNode> parseCondition(std::string ending = ")") const;

    /**
     * @brief Parses an inline Mindustry logic block.
     * @return The mindustry logic node.
     */
    std::unique_ptr<StatementNode> parseMindustryLogic() const;

    /**
     * @brief Parses an if statement.
     * @return The if node.
     */
    std::unique_ptr<ControlFlow> parseIf();

    /**
     * @brief Parses a while loop.
     * @return The while node.
     */
    std::unique_ptr<ControlFlow> parseWhile();

    /**
     * @brief Parses a for loop.
     * @return The for node.
     */
    std::unique_ptr<ControlFlow> parseFor();

    /**
     * @brief Parses a trigonometric function call and registers its op node.
     * @param resultName The result variable name.
     * @param value      The raw function token (e.g. "_sin").
     * @return The result variable name.
     */
    std::string parseTrig(std::string resultName, std::string value) const;

    /**
     * @brief Parses ++, -- or a compound assignment update.
     * @return The update node.
     */
    std::unique_ptr<VariableNode> parseIncrementDecrement();

    /**
     * @brief Parses and registers a variable declaration statement.
     */
    void variableDeclaration();

    /**
     * @brief Parses and registers a variable assignment statement.
     */
    void variableAssignment();

    /**
     * @brief Parses and registers an inline Mindustry logic statement.
     */
    void mindustryLogic();

    /**
     * @brief Parses and registers an if statement.
     */
    void If();

    /**
     * @brief Parses and registers a while statement.
     */
    void While();

    /**
     * @brief Parses and registers a for statement.
     */
    void For();

    /**
     * @brief Parses and registers an increment / decrement statement.
     */
    void IncrementDecrement();

    /**
     * @brief Asserts that the given variable has already been declared.
     * @param name The variable name to check.
     */
    void isVariableDeclared(std::string_view name) const;

    /**
     * @brief Asserts that the given variable has not yet been declared.
     * @param name The variable name to check.
     */
    void isVariableUndeclared(std::string_view name) const;

    /**
     * @brief Registers a variable name as declared.
     * @param name The variable name to add.
     */
    void addVariable(std::string_view name);

    Tokenizer* tokenizer_ = nullptr;
    std::stack<std::unique_ptr<AstNode>> rootNodes_;          ///< Stack of AST root nodes.
    spdlog::logger* debug_ = nullptr;
    std::vector<std::string> variables_;                      ///< Names of declared variables.
};
