#pragma once
#include <string>

/** @ingroup ASTNodes
 *  @brief The category of a statement within the source language.
 */
enum class StatementType {
    UNDEFINED,  ///< Default/unset state.
    ASSIGNMENT, ///< Variable assignment.
    OPERATION,  ///< Arithmetic / logic operation.
    IF,         ///< Conditional branch.
    LOOP,       ///< Loop construct (while / for).
    PRINT       ///< Output / print statement.
};

/** @ingroup ASTNodes
 *  @brief Base class for all statements in the AST.
 */
class StatementNode {
public:
    /**
     * @brief Serializes this statement to Mindustry logic code.
     * @return The generated logic code as a string.
     */
    virtual std::string toString() = 0;

    /** @brief Virtual destructor to allow polymorphic deletion. */
    virtual ~StatementNode() = default;
};
