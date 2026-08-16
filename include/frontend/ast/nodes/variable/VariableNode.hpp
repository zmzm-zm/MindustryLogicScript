#pragma once
#include <string>
#include <memory>
#include <frontend/ast/nodes/StatementNode.hpp>
#include <frontend/ast/nodes/expression/ExpressionNode.hpp>

/**
 * @defgroup Variable Variable
 * @ingroup ASTNodes
 * @brief Variable-related statements (declaration, initialization, assignment, update).
 */

/** @ingroup Variable
 *  @brief Base class for variable-related statements.
 */
class VariableNode : public StatementNode {
public:
    /**
     * @brief Constructs a variable statement node.
     * @param variable The name of the variable.
     * @param value    The expression providing the value (nullable).
     */
    VariableNode(std::string variable, std::unique_ptr<ExpressionNode> value);

    /**
     * @brief Returns the variable name.
     * @return The variable name string.
     */
    virtual std::string getVar() const;

protected:
    std::string variable_ = "^v^";            ///< The variable name.
    std::unique_ptr<ExpressionNode> value_;    ///< The value expression (nullable).
};
