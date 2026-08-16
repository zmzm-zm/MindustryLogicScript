#pragma once
#include "VariableNode.hpp"

/** @ingroup Variable
 *  @brief An update statement applying ++, --, or a compound assignment (+=, -=, *=, /=).
 */
class UpdateNode final: public VariableNode {
public:
    /**
     * @brief Constructs an update node with an optional value expression.
     * @param var   The target variable name.
     * @param op    The update operator (++, --, +=, -=, *=, /=).
     * @param value Optional expression providing the update value.
     */
    UpdateNode(std::string var, std::string op, std::unique_ptr<ExpressionNode> value = nullptr);

    /**
     * @brief Constructs an update node with an identifier operand.
     * @param var   The target variable name.
     * @param op    The update operator.
     * @param ident The identifier used as the operand.
     */
    UpdateNode(std::string var, std::string op, std::string ident);

    /** @brief Serializes the update to logic code. */
    std::string toString() override;

private:
    std::string op_ = "^v^";          ///< The update operator.
    std::string ident_ = "^v^";       ///< The identifier operand (for identifier form).
};
