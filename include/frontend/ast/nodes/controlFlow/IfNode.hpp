#pragma once
#include <frontend/ast/nodes/controlFlow/ControlFlow.hpp>

/** @ingroup ControlFlow
 *  @brief An if statement with a condition and a conditional body.
 */
class IfNode final: public ControlFlow {
public:
    /**
     * @brief Constructs an if node.
     * @param condition The condition expression.
     * @param body      The body executed when the condition is true.
     * @param line      The source line where the if appears.
     */
    IfNode(std::unique_ptr<ConditionNode> condition, std::unique_ptr<AstNode> body, std::size_t line);

    /** @brief Serializes the if statement to logic code. */
    std::string toString() override;
};